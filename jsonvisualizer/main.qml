import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

    Flickable {
        id: flickable
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredWidth: 1

        TextArea.flickable: TextArea {
            text: jsonString
            wrapMode: TextArea.Wrap
        }
        ScrollBar.vertical: ScrollBar { }
    }

    TableView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredWidth: 1

        delegate: Rectangle {
            color: "gray"
            border.color: "black"
            implicitWidth: 300
            implicitHeight: 80
            Text {
               anchors.fill: parent
               text: display
           }
        }
        model: paramsModel

    }

    }

}
