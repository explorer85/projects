import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout {
        anchors.fill: parent

    Flickable {
        id: flickable
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredHeight: 1

        TextArea.flickable: TextArea {
            text: jsonString
            wrapMode: TextArea.Wrap
        }
        ScrollBar.vertical: ScrollBar { }
    }

    ListView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredHeight: 1

    }

    }

}
