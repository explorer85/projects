import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
	visible: true
	width: 640
	height: 480
	title: qsTr("Hello World")


	StackView {
		id: stack
		anchors.fill: parent
		initialItem: fileLoadView

		AlgoProcessActivity {
			id : fileprocessView
			btn_back.onClicked: {
				algo.stopAlgo()
				stack.pop()
			}
		}
		LoadFileActivity {
			id : fileLoadView
		}


	}
}
