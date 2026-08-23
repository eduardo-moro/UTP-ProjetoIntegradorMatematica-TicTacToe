import QtQuick
import QtQuick.Layouts

Item {
    id: gameScene
    anchors.centerIn: parent
    
    property int gameMode: GameModeEnum.GameMode.Versus

    width: 420
    height: 500

    signal backToMenu


    Loader {
        id: mediaLoader
        source: "qrc:/qml/MediaPlayerComponent.qml"
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
        text: gameEngine.currentPlayer
        font.family: "Comic Sans MS"
        font.pixelSize: 30
        anchors.top: gameScene.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 50
        color: Colors.yellow2
    }

    GridLayout {
        id: grid
        columns: 3
                
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: gameScene.top
        anchors.topMargin: 130

        width: 320
        height: 320

        function cellClicked(pos) {
            gameEngine.makeMove(pos)
            
            if (mediaLoader.active && mediaLoader.item) {
                mediaLoader.item.stop()
                mediaLoader.item.play()
            }
        }

        Repeater {
            model: 9
            delegate: GameButton {
                value: {
                    if (gameEngine && gameEngine.boardState && index < gameEngine.boardState.length) {
                        return gameEngine.boardState[index]
                    }
                    return 0
                }
                onClicked: grid.cellClicked(index)

                btnIndex: index
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
            }
        }
    }
}
