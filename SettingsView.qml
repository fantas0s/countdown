import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs as Dialogs
import Qt.labs.platform as Labs

Item {
    width: 800
    height: 600
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_background_image_before_timeout")
            }
            TextField {
                text: _appLogic.backgroundImageFileName
                enabled: false
                Layout.fillWidth: true
            }
            Button {
                text: _appLogic.defaultBackgroundImage ? qsTrId("button_select_file") : qsTrId("button_restore_default_file")
                onClicked: {
                    if (_appLogic.defaultBackgroundImage)
                        _imagePicker.open()
                    else
                        _appLogic.backgroundImage = ""
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_background_image_after_timeout")
            }
            TextField {
                text: _appLogic.timeoutBackgroundImageFileName
                enabled: false
                Layout.fillWidth: true
            }
            Button {
                text: _appLogic.defaultTimeoutBackgroundImage ? qsTrId("button_select_file") : qsTrId("button_restore_default_file")
                onClicked: {
                    if (_appLogic.defaultTimeoutBackgroundImage)
                        _timeoutImagePicker.open()
                    else
                        _appLogic.timeoutBackgroundImage = ""
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_view_title")
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
                border.width: 1
                border.color: "black"
            }
            Button {
                text: qsTrId("button_change_color")
                onClicked: _titleColorPicker.open()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_info_before_timeout")
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
                border.width: 1
                border.color: "black"
            }
            Button {
                text: qsTrId("button_change_color")
                onClicked: _infoColorPicker.open()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_info_after_timeout")
            }
            TextField {
                Layout.fillWidth: true
                onTextChanged: _appLogic.timeOutInfoText = text
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: qsTrId("label_textfield_title_timeout_datetime")
            }
            TextField {
                Layout.fillWidth: true
                text: _appLogic.timeoutTimeString
                enabled: false
            }
            TextField {
                implicitWidth: 1.5 * implicitHeight
                maximumLength: 2
                onTextChanged: _appLogic.targetHour = Number(text)
            }
            Label {
                text: qsTrId("separator_hour")
            }
            TextField {
                implicitWidth: 1.5 * implicitHeight
                maximumLength: 2
                onTextChanged: _appLogic.targetMinute = Number(text)
            }
            Rectangle {
                width: height
                height: _timeColorButton.implicitHeight
                color: _appLogic.timerColor
                border.width: 1
                border.color: "black"
            }
            Button {
                id: _timeColorButton
                text: qsTrId("button_change_color")
                onClicked: _timerColorPicker.open()
            }
        }
    }
    Dialogs.FileDialog {
        id: _imagePicker
        nameFilters: [qsTrId("filefilter_option_image_files"), qsTrId("filefilter_option_all_files")]
        onAccepted: _appLogic.backgroundImage = selectedFile
    }
    Dialogs.FileDialog {
        id: _timeoutImagePicker
        nameFilters: [qsTrId("filefilter_option_image_files"), qsTrId("filefilter_option_all_files")]
        onAccepted: _appLogic.timeoutBackgroundImage = selectedFile
    }
    Labs.ColorDialog {
        id: _titleColorPicker
        onColorChanged: _appLogic.titleColor = color
    }
    Labs.ColorDialog {
        id: _infoColorPicker
        onColorChanged: _appLogic.infoColor = color
    }
    Labs.ColorDialog {
        id: _timerColorPicker
        onColorChanged: _appLogic.timerColor = color
    }
}
