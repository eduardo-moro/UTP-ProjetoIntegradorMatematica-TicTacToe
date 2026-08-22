import QtQuick

Item {
    id: root
    signal clicked()

    property int w: 100
    property int h: 100
    
    property int fs: 28

    property string label: "botão"
    property string c: "#ffffff"

    Rectangle {
        id: button
        width: root.w
        height: root.h
        anchors.centerIn: parent
        color: "#3c3836"
        radius: 12
        border.color: "#504945"

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
            text: root.label
            font.pixelSize: root.fs
            font.bold: true
            font.family: "Comic Sans MS"
            color: root.c
            opacity: root.label === "" ? 0 : 1
            scale: root.label === "" ? 0.3 : 1

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
            button.r = Math.random() * 25 - 15
        }

        function buttonReleased() {
            button.r = 0
        }

        function buttonClicked() {
            root.clicked()
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onPressed: button.buttonPressed();
            onReleased: button.buttonReleased();
            onClicked: button.buttonClicked();
        }
    }
}
