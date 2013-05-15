import QtQuick 2.0

ListView {
    width: 200; height: 250;

    model: slideShow;
    delegate: Text { text: slideText }
}
