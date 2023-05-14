import QtQuick.Controls

Dialog {
    title: qsTr("Settings")
    contentItem: SettingsView {}
    standardButtons: Dialog.Save | Dialog.Cancel
}
