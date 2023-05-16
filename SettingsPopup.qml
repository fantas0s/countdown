import QtQuick.Controls

Dialog {
    title: qsTr("Settings")
    modal: true
    contentItem: SettingsView {}
    standardButtons: Dialog.Save
}
