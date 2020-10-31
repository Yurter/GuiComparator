import QtQuick 2.14
import QtQuick.Window 2.14
import Qt.labs.platform 1.1

Window {
    id: root
    visible: true
    color: 'transparent'
    width: 640
    height: 480
    flags: Qt.Tool | Qt.WindowTitleHint | Qt.WindowStaysOnTopHint

    SystemTrayIcon {
        visible: true
        icon.source: 'qrc:/img/compare.png'
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
        onActivated: {
            if (reason === SystemTrayIcon.Trigger) {
                reset()
                root.show()
            }
        }
    }
    Shortcut {
        context: Qt.ApplicationShortcut
        sequence: "Ctrl+W"
        onActivated: root.hide()
    }
    Timer {
        id: timer
        interval: 50
        onTriggered: {
            image.source = screenshot.makeBase64Screenshot(
                Qt.rect(root.x, root.y, root.width, root.height)
            )
        }
    }
    Image {
        id: image
        anchors.fill: parent
    }
    Item {
        id: moveHander
        anchors.fill: parent
        focus: true

        Keys.onLeftPressed:  --root.x
        Keys.onRightPressed: ++root.x
        Keys.onUpPressed:    --root.y
        Keys.onDownPressed:  ++root.y

        Keys.onSpacePressed: makeScreenshot()
        Keys.onEscapePressed: root.hide()
        Keys.onBackPressed: reset()
    }
    TapHandler {
        onTapped: makeScreenshot()
    }

    function makeScreenshot() {
        reset()
        timer.start()
    }
    function reset() {
        image.source = ""
    }
}
