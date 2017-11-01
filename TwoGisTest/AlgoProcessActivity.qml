import QtQuick 2.7
import QtQuick.Controls 2.0

Item {
	property alias btn_back: btn_back


	Rectangle {
		anchors.fill: parent
		color: "blue"


		Button {
			id: btn_back
			width: 100
			height: 100
			text: "Назад"
			anchors.centerIn: parent
		}


		Column {
			anchors.top: btn_back.bottom
			anchors.horizontalCenter: btn_back.horizontalCenter
			anchors.topMargin: 10
			spacing: 2
			Text {
				id: parsedStringsCount
				color: "white"
			}

			Text {
				id: parsedWordsCount
				color: "white"

			}
			Text {
				id: uniqueWordsCount
				color: "white"
			}
		}




//		Button {
//			x: 300
//			width: 100
//			height: 100
//			text: "yyyyy"
//			anchors.fill: parent
//			onClicked: fparser.startParsing("777")

//		}




	}


	Connections {
	target: fparser

	onLineProcessed: {

		parsedStringsCount.text = "Строк обработано:" + parseInt(totalStringsCount)
		parsedWordsCount.text = "Слов найдено: " + parseInt(totalWordsCount)
		uniqueWordsCount.text = "Уникальных слов найдено: "
		console.log("onLineProcessed  " + totalStringsCount)

	}


	}

}
