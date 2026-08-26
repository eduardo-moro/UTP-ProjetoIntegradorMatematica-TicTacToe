import QtQuick

Item {
    id: root
    signal clicked()
    property int value: 0
    property int btnIndex;
    property bool highlighted: false

    Rectangle {
        id: cell
        width: 100
        height: 100
        anchors.centerIn: parent
        color: Colors.bg1
        radius: 12
        border.color: root.highlighted ? Colors.orange2 : Colors.bg2
        border.width: root.highlighted ? 3 : 1

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
            text: root.value === 1 ? "X" : (root.value === 2 ? "O" : "")
            font.pixelSize: 48
            font.bold: true
            font.family: "Comic Sans MS"
            color: Colors.fg1
            opacity: root.value === 0 ? 0 : 1
            scale: root.value === 0 ? 0.3 : 1

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
            if (root.value == 0) {
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
