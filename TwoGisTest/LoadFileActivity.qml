import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


Item {


	Rectangle {
		id: fileLoadRect
		color: "red"
		anchors.fill: parent

		Button {
			width: 100
			height: 100
			text: "Открыть \n файл"
			visible: true
			anchors.centerIn: parent
			onClicked: {
				fileDialog.visible = true

			}
		}
	}


	FileDialog {
		id: fileDialog
		title: "Please choose a file"
		folder: shortcuts.home
		modality: Qt.ApplicationModal

		onAccepted: {
			//console.log("You chose: " + fileDialog.fileUrl)
			var tmpUrl = fileDialog.fileUrl.toString()
			visible = false
			stack.push(fileprocessView)
			fparser.startParsing(tmpUrl.substring(7, tmpUrl.length))
		}
		onRejected: {
			console.log("Canceled")
			visible = false
		}
		Component.onCompleted: visible = false
	}

}








