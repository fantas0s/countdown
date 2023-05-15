import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform

Item {
    width: 800
    height: 600
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Background image")
            }
            TextField {
                text: _appLogic.backgroundImageFileName
                enabled: false
                Layout.fillWidth: true
            }
            Button {
                text: _appLogic.defaultBackgroundImage ? qsTr("Select") : qsTr("Restore default")
                onClicked: _imagePicker.open()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Title text")
            }
            TextField {
                id: _titleField
                Layout.fillWidth: true
                onTextChanged: _appLogic.titleText = text
            }
            Rectangle {
                width: height
                height: _titleField.implicitHeight
                color: _appLogic.titleColor
            }
            Button {
                text: qsTr("Change color")
                onClicked: _titleColorPicker.open()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Info text")
            }
            TextField {
                id: _infoField
                Layout.fillWidth: true
                onTextChanged: _appLogic.infoText = text
            }
            Rectangle {
                width: height
                height: _infoField.implicitHeight
                color: _appLogic.infoColor
            }
            Button {
                text: qsTr("Change color")
                onClicked: _infoColorPicker.open()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Info text after timeout")
            }
            TextField {
                Layout.fillWidth: true
                onTextChanged: _appLogic.timeOutInfoText = text
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTr("Timer end time")
            }
            TextField {
                Layout.fillWidth: true
                text: _appLogic.timeoutTimeString
                enabled: false
            }
            Tumbler {
                implicitHeight: 100
                model: 24
                delegate: delegateComponent
                onCurrentIndexChanged: _appLogic.targetHour = currentIndex
            }
            Tumbler {
                implicitHeight: 100
                model: 60
                delegate: delegateComponent
                onCurrentIndexChanged: _appLogic.targetMinute = currentIndex
            }
            Rectangle {
                width: height
                height: _infoField.implicitHeight
                color: _appLogic.timerColor
            }
            Button {
                text: qsTr("Change color")
                onClicked: _timerColorPicker.open()
            }
        }
    }
    Component {
        id: delegateComponent
        Label {
            text: modelData
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
