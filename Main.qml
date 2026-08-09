import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import "content"

Window {
    id: root
    width: 420
    height: 500
    visible: true
    title: "tic tac toe"
    color: "#1a1a1a"

    Text {
        id: title
        visible: true
        text: "tic tac toe"
        font.pixelSize: 38
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        color: "#ffffff"
    }


    Loader {
        id: mediaLoader
        source: "qrc:/content/MediaPlayerComponent.qml"
    }

    GridLayout {
        id: grid
        columns: 3
        anchors.centerIn: parent

        width: 320
        height: 320

        property bool isOddPlayer: false

        function cellClicked() {
            isOddPlayer = isOddPlayer === true ? false : true
            if (mediaLoader.active && mediaLoader.item) {
                mediaLoader.item.stop()
                mediaLoader.item.play()
            }
        }

        Repeater {
            model: 9
            delegate: Button {
                isOddPlayer: grid.isOddPlayer
                onClicked: grid.cellClicked()
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
            }
        }
    }
}
