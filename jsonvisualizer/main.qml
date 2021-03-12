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
            readOnly: true
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
            id: delegateRoot
            color: !nsgbrhighlight ? "gray" : "green"

            border.color: "black"
            implicitWidth: 300
            implicitHeight: 180
            TextArea {
                id: tfEdit
                anchors.fill: parent
                visible: true
                text: display
                onTextChanged: {
                    if (text != display) {
                        setParam = text
                    }

                }

            }
        }
        model: paramsModel
    }
    Button {
        text: "Save to file"
        onClicked: {
          paramsModel.saveModelData();
        }
    }

    }

}
