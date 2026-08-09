import QtQuick

Item {
    id: root
    signal clicked()
    property string playerChar

    Rectangle {
        id: cell
        width: 100
        height: 100
        anchors.centerIn: parent
        color: "#2b2b2b"
        radius: 12
        border.color: "#444444"

        property string mark: ""

        scale: mouseArea.pressed ? 0.92 : 1.00

        Behavior on scale {
            NumberAnimation {
                duration: 100
                easing.type: Easing.OutBack
            }
        }

        property real r: 0

        rotation: r

        Text {
            anchors.centerIn: parent
            text: cell.mark
            font.pixelSize: 48
            font.bold: true
            color: "#e74c3c"
            opacity: cell.mark === "" ? 0 : 1
            scale: cell.mark === "" ? 0.3 : 1

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
                }
            }

            Behavior on scale {
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.OutBack
                }
            }
        }

        function buttonPressed() {
            cell.r = Math.random() * 25 - 15
        }

        function buttonReleased() {
            cell.r = 0
        }

        function buttonClicked() {
            if (cell.mark === "") {
                cell.mark = root.playerChar
                root.clicked()
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onPressed: cell.buttonPressed();
            onReleased: cell.buttonReleased();
            onClicked: cell.buttonClicked();
        }
    }
}
