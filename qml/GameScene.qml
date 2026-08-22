import QtQuick
import QtQuick.Layouts

Item {
    id: gameScene
    anchors.centerIn: parent
    
    property int gameMode: GameModeEnum.GameMode.Neo

    width: 420
    height: 500

    signal backToMenu


    Loader {
        id: mediaLoader
        source: "qrc:qml/MediaPlayerComponent.qml"
    }

    Button{
        id: returnButton
        anchors.top: gameScene.top
        anchors.topMargin: 70
        anchors.left: parent.left
        anchors.leftMargin: 70

        w: 42
        h: 42
        fs: 12

        label: "<"
        onClicked: backToMenu()
    }

    Text {
        id: title
        visible: true
        text: ["versus", "facil", "médio", "dificil", "neo"][gameMode]
        font.family: "Comic Sans MS"
        font.pixelSize: 30
        anchors.top: gameScene.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 50
        color: "#fabd2f"
    }

    GridLayout {
        id: grid
        columns: 3
                
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: gameScene.top
        anchors.topMargin: 130

        width: 320
        height: 320

        property bool isOddPlayer: false

        function checkWin() {
            var cell0 = children[0].children[0].mark
            var cell1 = children[1].children[0].mark
            var cell2 = children[2].children[0].mark

            if (cell0 !== "" && cell0 === cell1 && cell1 === cell2) {
                return cell0
            }
            return null
        }

        function cellClicked() {
            isOddPlayer = isOddPlayer === true ? false : true
            if (mediaLoader.active && mediaLoader.item) {
                mediaLoader.item.stop()
                mediaLoader.item.play()
            }

            var winner = checkWin()
            if (winner) {
                title.text = "Player " + winner + " won!"

                children.map((cell) => {
                    cell.children[0].mark = ""
                })
            }
        }

        Repeater {
            model: 9
            delegate: GameButton {
                isOddPlayer: grid.isOddPlayer
                onClicked: grid.cellClicked()
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
            }
        }
    }
}
