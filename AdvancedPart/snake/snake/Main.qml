import QtQuick
import QtQuick.Controls

Window {
    width: snake.sourceSize.width
    height: snake.sourceSize.height
    visible: true
    AnimatedImage {
        id: snake
        source: "Assets/Hoolheyak-Relax-x1-right.gif"
        fillMode: Image.PreserveAspectFit
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
