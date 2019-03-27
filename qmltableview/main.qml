import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("TableView")

    TableView {
        anchors.fill: parent
        TableViewColumn {
            role: "id"
            title: "Id"
            width: 100
        }
        TableViewColumn {
            role: "name"
            title: "Name"
            width: 200
        }
        TableViewColumn {
            role: "phone"
            title: "PhoneNumber"
            width: 200
        }
        model: phonebookmodel
    }







}
