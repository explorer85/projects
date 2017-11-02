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
			id: btnLoad
			width: 100
			height: 100
			text: "Открыть \n файл"
			visible: true
			anchors.centerIn: parent
			onClicked: {
				fileDialog.visible = true
				//console.log(amanager.getAlgoList())

			}
		}


		ComboBox {
			anchors.top: btnLoad.bottom
			anchors.horizontalCenter: btnLoad.horizontalCenter
			anchors.topMargin: 10
			width: 200
			editable: false
			model:amanager.getAlgoList()
			onActivated: {
				//console.log(model[index])
				amanager.createAlgo(model[index])

			}
			Component.onCompleted: {
				amanager.createAlgo(model[currentIndex])
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
			if (tmpUrl) {
				visible = false
				stack.push(fileprocessView)
				//algo.function()
				algo.startAlgo(tmpUrl.substring(7, tmpUrl.length))
			}
		}
		onRejected: {
			console.log("Canceled")
			visible = false
		}
		Component.onCompleted: visible = false
	}

}








