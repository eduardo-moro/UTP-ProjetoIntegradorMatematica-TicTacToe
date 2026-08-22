import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import "tic-tac-toe"

Window {
    id: root
    width: 420
    height: 500
    visible: true
    title: "tic tac toe"
    color: Colors.bg0_hard

    property int mode: GameModeEnum.GameMode.Versus    
    property bool menu: true

    function startGame (m) {
        mode = m
        menu = false
    }

    StartMenu {
        z: 10
        id: startMenu
        visible: menu
        onStartGame: (m) => root.startGame(m)
        opacity: menu ? 1 : 0

        Behavior on visible{
            NumberAnimation {
                duration: 1200
            }
        }

        Behavior on opacity{
            NumberAnimation {
                duration: 1000
            }
        }
    }

    GameScene {
        z: 0
        id: gameScene
        visible: !menu
        opacity: !menu ? 1 : 0
        gameMode: mode
        onBackToMenu: menu = true

        Behavior on visible{
            NumberAnimation {
                duration: 1200
            }
        }

        Behavior on opacity{
            NumberAnimation {
                duration: 1400
            }
        }
    }
}
