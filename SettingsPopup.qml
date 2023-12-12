import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: _settingsRoot
    signal close
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        SettingsView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Button {
            Layout.alignment: Qt.AlignRight
            text: qsTrId("button_save")
            onClicked: _settingsRoot.close()
        }
    }
}
