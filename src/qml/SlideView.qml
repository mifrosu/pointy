import QtQuick 2.0
import QtQuick.Window 2.0

Rectangle {
    id: mainView;
    width: 800; height: 600;
    property bool notesVisable: true;
    property bool horizontalLayout: true;

    Rectangle {
        id: fadeRectangle;
        width: mainView.width; height: mainView.height;
        color: dataView.currentItem.pointyStageColor;
        opacity: 1.0;
    }

    ListView {

        id: dataView;
        property bool moveForward;
        opacity: 1.0;
        //interactive: false;
        snapMode: ListView.SnapToItem;
        width: parent.width; height: parent.height;
        anchors.fill: parent;
        keyNavigationWraps: true;
        highlightFollowsCurrentItem: true;
        highlightRangeMode: "StrictlyEnforceRange";
        highlightMoveDuration: 0;
        orientation: {
            (mainView.horizontalLayout) ? Qt.Horizontal : Qt.Vertical;
        }

        model: slideShow;

        delegate: PointySlide {
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
            if (pointyTransition === "fade") {
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
                from: 1.0; to: 0.3; duration: 500;
            }
            ScriptAction {
                script: {
                    dataView.moveSlide();
                }
            }
            NumberAnimation {
                target: dataView;
                properties: "opacity";
                from: 0.3; to: 1.0; duration: 500;
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


        focus: true;
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
        }

    } // ListView

    Window {
        id: notesTextWindow;
        width: 400; height: 300;

        title: "Pointy Notes"
        visible: mainView.notesVisable;

        Text {
            anchors.fill: parent
            anchors.margins: parent.height * 0.1;

            font.pixelSize: 16
            wrapMode: Text.WordWrap

            property string notes: dataView.currentItem.pointyNotes;
            text: notes == "" ? "This slide has no notes." : notes;
            font.italic: notes == "";
        }
    } // Window


} // Rectangle


