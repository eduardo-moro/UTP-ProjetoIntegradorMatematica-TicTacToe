import QtQuick
import QtMultimedia

MediaPlayer {
    id: mediaPlayer
    audioOutput: AudioOutput {}
    source: "qrc:/assets/button.wav"
}
