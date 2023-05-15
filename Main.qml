import QtQuick
import QtQuick.Controls

Rectangle {
    id: _root
    color: "black"
    Image {
        source: _appLogic.backgroundImage
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
        Label {
            id: _titleText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: parent.height / 15
            font.pixelSize: parent.height / 15
            color: _appLogic.titleColor
            text: _appLogic.titleText
        }
        Label {
            id: _infoText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: _titleText.bottom
            anchors.topMargin: parent.height / 15
            font.pixelSize: parent.height / 10
            color: _appLogic.infoColor
            text: _appLogic.displayText
        }
        Label {
            id: _timerText
            anchors.centerIn: parent
            font.pixelSize: parent.height / 5
            color: _appLogic.timerColor
            text: _appLogic.timerText
        }
        Button {
            id: _closeButton
            text: qsTr("Close")
            anchors.right: parent.right
            anchors.top: parent.top
            opacity: _buttonTimer.buttonsVisible ? 1.0 : 0.0
            hoverEnabled: true
            onClicked: Qt.quit()
        }
        Button {
            id: _collapseButton
            text: _appLogic.expandCollapseText
            anchors.right: _closeButton.left
            anchors.top: parent.top
            opacity: _buttonTimer.buttonsVisible ? 1.0 : 0.0
            hoverEnabled: true
            onClicked: _appLogic.expandCollapse()
        }
        Button {
            id: _settingsButton
            text: qsTr("Settings")
            anchors.right: _collapseButton.left
            anchors.top: parent.top
            opacity: _buttonTimer.buttonsVisible ? 1.0 : 0.0
            hoverEnabled: true
            onClicked: _settingsDialog.open()
        }
    }
    Timer {
        id: _buttonTimer
        property bool buttonsVisible: false
        property bool buttonsHovered: _settingsButton.hovered || _collapseButton.hovered || _closeButton.hovered
        onButtonsHoveredChanged: {
            if (buttonsHovered)
            {
                buttonsVisible = true
                stop()
            }
            else
            {
                restart()
            }
        }
        repeat: false
        interval: 2000
        onTriggered: buttonsVisible = false
    }
    SettingsPopup {
        id: _settingsDialog
        x: _root.width / 2 - (_settingsDialog.width / 2)
        y: _root.height / 2 - (_settingsDialog.height / 2)
    }
}
