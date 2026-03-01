import QtQuick
import QtQuick.Controls
import QtMultimedia

Window {
    width: snake.sourceSize.width
    height: snake.sourceSize.height
    visible: true
    MediaPlayer {
        id: snake
        source: "Assets/Hoolheyak-Move-x1-right.webm"
        videoOutput: videoOutput
        autoPlay: true
    }
    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton|Qt.RightButton

        onClicked: (mouse) => {
                       if (mouse.button === Qt.RightButton) {
                           rightClickMenu.popup()
                       }
                   }
    }
    Menu {
        id: rightClickMenu
        MenuItem {
            text: "add"

        }
        MenuItem {
            text: "attach"

        }
        MenuItem {
            text: "delete"

        }
    }
}
