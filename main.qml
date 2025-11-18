// Import necessary QML modules
import QtQuick
import QtQuick.Window

// The main application window
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Cryptonite")

    // A simple colored rectangle to fill the background
    Rectangle {
        anchors.fill: parent
        color: "#2c3e50" // A dark blue-gray color
    }

    // A text label centered in the window
    Text {
        anchors.centerIn: parent
        text: qsTr("Minimal QML Application")
        color: "white"
        font.pixelSize: 24
    }
}
