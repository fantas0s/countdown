import QtQuick.Controls

Dialog {
    title: qsTrId("title_settings")
    modal: true
    contentItem: SettingsView {}
    standardButtons: Dialog.Save
}
