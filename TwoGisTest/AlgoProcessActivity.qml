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
				id: parsedUniqueWordsCount
				color: "white"
			}
			Text {
				id: algoResult
				color: "white"
			}

		}


	}


	Connections {
	target: algo

	onAlgoFinished: {
	  result ?	algoResult.text = "Файл обработан" : "Файл не обработан"
	}

	onLineProcessed: {

		parsedStringsCount.text = "Строк обработано:" + parseInt(totalStringsCount);
		parsedWordsCount.text = "Слов найдено: " + parseInt(totalWordsCount);
		parsedUniqueWordsCount.text = "Уникальных слов найдено: " + parseInt(uniqueWordsCount);

		//console.log("onLineProcessed  " + totalStringsCount)

	}




	}

}
