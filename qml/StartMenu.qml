import QtQuick
import QtQuick.Layouts

Item {
    id: root

    signal startGame(int gameMode)

    Rectangle{
        id: container
        width: 420
        height: 500
        color: "#1d2021"
        
        GridLayout {
            id: options
            columns: 1

            width: 420
            height: 250

            anchors.top: container.top 
            anchors.topMargin: 100


            Repeater{
                model: 5

                delegate: Button {
                    w: 240
                    h: 42

                    label: ["versus", "facil", "médio", "dificil", "neo"][index]
                    c: "#f3f3f3"
                    fs: 20

                    property int value: [GameModeEnum.GameMode.Versus, GameModeEnum.GameMode.Easy, GameModeEnum.GameMode.Medium, GameModeEnum.GameMode.Hard, GameModeEnum.GameMode.Neo][index]

                    onClicked: root.startGame(value)

                    Layout.fillHeight: true
                    Layout.fillWidth: true    
                }
            }            
        }
    }
}
