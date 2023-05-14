import QtQuick
import QtQuick.Controls

Item {
    id: _root
    Image {
        source: _appLogic.backgroundImage
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent
        Label {
            id: _titleText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: parent.height / 15
            font.pixelsize: parent.height / 15
            color: _appLogic.titleColor
            text: _appLogic.titleText
        }
        Label {
            id: _infoText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: _titleText.bottom
            anchors.topMargin: parent.height / 15
            font.pixelsize: parent.height / 10
            color: _appLogic.infoColor
            text: _appLogic.infoText
        }
        Label {
            id: _timerText
            anchors.centerIn: parent
            font.pixelsize: parent.height / 5
            color: _appLogic.timerColor
            text: _appLogic.timerText
        }
        Button {
            id: _closeButton
            text: qsTr("close")
            anchors.right: parent.right
            anchors.top: parent.top
            visible: _buttonTimer.buttonsVisible
            hoverEnabled: true
            onClicked: Qt.quit()
        }
        Button {
            id: _collapseButton
            text: appLogic.expandCollapseText
            anchors.right: _closebutton.left
            anchors.top: parent.top
            visible: _buttonTimer.buttonsVisible
            hoverEnabled: true
            onClicked: appLogic.expandCollapse()
        }
        Button {
            id: _settingsButton
            text: qsTr("settings")
            anchors.right: _collapseButton.left
            anchors.top: parent.top
            visible: _buttonTimer.buttonsVisible
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
                buttonsVisible = true
            else
                restart()
        }
        repeat: false
        interval: 2000
        onTriggered: buttonsVisible = false
    }
    SettingsPopup {
        id: _settingsDialog
    }
}
