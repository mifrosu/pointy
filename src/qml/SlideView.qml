import QtQuick 2.0
import QtQuick.Window 2.0


Rectangle {
    id: mainView;
    width: 800; height: 600;
    property bool notesVisible: true;
    property bool gridVisible: true;
    property bool horizontalLayout: true;

    signal toggleScreenMode();
    signal quitPointy();

    Rectangle {
        id: fadeRectangle;
        width: mainView.width; height: mainView.height;
        color: dataView.currentItem.pointyStageColor;
        opacity: 1.0;
    }

    ListView {

        id: dataView;
        focus: true;
        property bool moveForward;
        opacity: 1.0;
        //interactive: false;
        snapMode: ListView.SnapToItem;
        keyNavigationWraps: true;
        highlightFollowsCurrentItem: true;
        highlightRangeMode: "StrictlyEnforceRange";
        highlightMoveDuration: 0;
        orientation: {
            (mainView.horizontalLayout) ? Qt.Horizontal : Qt.Vertical;
        }

        model: slideShow;

        delegate:
            PointySlide {
            slideWidth: mainView.width;
            slideHeight: mainView.height;

        }

        property int slideCount: count;

        currentIndex: {
            if (slideCount > 0){
                return 1;
            }
            else {
                return 0;
            }
        }

        Timer {
            id: waitTime;
            interval: 500;
            repeat: false;
        }

        function moveSlide() {
            if (dataView.moveForward === true) {
                dataView.currentIndex +=1 ;
            }
            else if (dataView.moveForward === false) {
                dataView.currentIndex -= 1;
            }
        }

        function loadTransition(pointyTransition) {
            if (dataView.opacity != 0.0) {
                animateFade.start();
            }
            else {
                moveSlide();
            }
        }

        SequentialAnimation  {
            id: animateFade;
            NumberAnimation {
                target: dataView;
                // target: fadeRectangle;
                properties: "opacity";
                from: 1.0; to: 0.3; duration: 200;
            }
            ScriptAction {
                script: {
                    dataView.moveSlide();
                }
            }
            NumberAnimation {
                target: dataView;
                properties: "opacity";
                from: 0.3; to: 1.0; duration: 200;
            }
        }

        NumberAnimation {
            id: blankScreen;
            target: dataView;
            properties: "opacity";
            from: 1.0; to: 0.0; duration: 800;
        }

        NumberAnimation {
            id: revealScreen;
            target: dataView;
            properties: "opacity";
            from: 0.0; to: 1.0; duration: 800;
        }

        function toggleScreenBlank() {
            if (dataView.opacity != 0.0) {
                blankScreen.start();
            }
            else {
                revealScreen.start();
            }
        }


        MouseArea {
            id: mouseArea;
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if (mouse.button === Qt.LeftButton) {
                    console.log("Left!")
                }
                else {
                    console.log("Right")
                }
            }
        }

        function toggleWindow(windowId) {
            if (windowId.visible === true) {
                windowId.visible = false;
            }
            else {
                windowId.show();
            }

        }



        Keys.onPressed: {
            if (event.key === Qt.Key_Space && (currentIndex < slideCount -1)) {
                dataView.moveForward = true;
                loadTransition(dataView.currentItem.pointyTransition);

                //currentIndex += 1;
            }

            else if (event.key === Qt.Key_Backspace && currentIndex > 1) {
                dataView.moveForward = false;
                loadTransition(dataView.currentItem.pointyTransition);
                //currentIndex -=1;
            }

            else if (event.key === Qt.Key_Return &&
                                dataView.currentItem.isMediaSlide === true ) {
                dataView.currentItem.mediaSignal();
            }


            if (event.key === Qt.Key_Less &&
                    dataView.currentItem.isMediaSlide === true ) {
                dataView.currentItem.backMedia();
            }
            else if (event.key === Qt.Key_Greater &&
                     dataView.currentItem.isMediaSlide === true ) {
                dataView.currentItem.forwardMedia();

            }




            else if (event.key === Qt.Key_F ||
                     event.key === Qt.Key_F11 ) {
                toggleScreenMode();
            }
            else if (event.key === Qt.Key_Q ||
                     event.key === Qt.Key_Escape) {
                quitPointy();
            }
            else if (event.key === Qt.Key_B) {
                toggleScreenBlank();
            }
            else if (event.key === Qt.Key_N) {
                toggleWindow(notesTextWindow);
            }
            else if (event.key === Qt.Key_G) {
                toggleWindow(gridViewWindow);
            }
        }

    } // ListView

    Window {
        id: notesTextWindow;
        width: 400; height: 300;

        title: "Pointy Notes"
        visible: mainView.notesVisible;

        Text {
            focus: true;
            anchors.fill: parent
            anchors.margins: parent.height * 0.1;

            font.pixelSize: 16
            wrapMode: Text.WordWrap

            property string notes: dataView.currentItem.pointyNotes;
            text: notes == "" ? "This slide has no notes." : notes;
            font.italic: notes == "";

            Keys.onPressed: {
                if (event.key === Qt.Key_N) {
                    if (notesTextWindow.visible === true )
                    {
                        notesTextWindow.visible = false;
                    }
                }
            }
        }
    } // Window (notesTextWindow)

    Window {
        id: gridViewWindow;
        width: 400; height: 300;

        title: "Pointy Grid View"
        visible: mainView.gridVisible;

        GridView {
            id: gridView;
            model: slideShow;
            focus: true;
            width: parent.width; height: parent.height;
            currentIndex: dataView.currentIndex;
            snapMode: GridView.SnapToRow;

            cellWidth: {width/2;}
            cellHeight: {height/2;}

            delegate: PointySlide {
                width: {gridView.cellWidth - 5}
                height: {gridView.cellHeight - 5}
                slideWidth: width;
                slideHeight: height;
                scaleFactor: {
                    width/mainView.width;
                }
                MouseArea {
                    id: mouseGridArea;
                    anchors.fill: parent;
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        if (mouse.button === Qt.LeftButton) {
                            // index role is available to delegate
                            dataView.currentIndex = index;
                        }
                        else {
                            console.log("Right")
                        }
                    }
                }
            }

            highlight: Rectangle {
                border.color: "#ffae00"
                color: "transparent";
                opacity: 1.0;
                border.width: 1;
                radius: 2;

                width: gridView.cellWidth;
                height: gridView.cellHeight;
                x: gridView.currentItem.x;
                y: gridView.currentItem.y;
                z: {gridView.currentItem.z + 1;}    // put highlight on top
                Rectangle {
                    width: parent.width;
                    height: parent.height;
                    opacity: 0.2;
                    color: "gold";
                    radius: parent.radius;
                }

            }


            Keys.onPressed: {
                if (event.key === Qt.Key_G) {
                    if (gridViewWindow.visible === true )
                    {
                        gridViewWindow.visible = false;
                    }
                }
                if (event.key === Qt.Key_Return) {
                    dataView.currentIndex = currentIndex;
                }
            }
            highlightFollowsCurrentItem: true;
            highlightMoveDuration: 0;

        }
    }


} // Rectangle


