import QtQuick 2.0
import QtQuick.Window 2.0

Rectangle {
    id: mainView;
    width: 400; height: 300;
    property bool notesVisable: true;
    property bool horizontalLayout: true;

    ListView {
        id: dataView;
        snapMode: ListView.SnapToItem;
        width: parent.width; height: parent.height;
        anchors.fill: parent;
        keyNavigationWraps: true;
        highlightFollowsCurrentItem: true;
        highlightRangeMode: "StrictlyEnforceRange";
        orientation: {
            (mainView.horizontalLayout) ? Qt.Horizontal : Qt.Vertical;
        }

        model: slideShow;
        // To visualize data, bind the view's model property to a model
        // and the delegate property to a component

        delegate: PointySlide {
            slideWidth: mainView.width;
            slideHeight: mainView.height;
        }

        property int slideCount: count;

        currentIndex: {
            if (slideCount > 0) {
                return 1;
            } else {
                return 0;
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
            if (event.key === Qt.Key_Space) {
                console.log("SPACE!")
                if (currentIndex < slideCount-1) {
                    currentIndex +=1;
                }
            }
            else if (event.key === Qt.Key_Backspace) {
                if (currentIndex > 1) {
                    currentIndex -=1;
                }
            }
        }

    }
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
    }
}


