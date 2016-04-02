import QtQuick 2.5
import QtQuick.Window 2.2
import RadarLine 1.0

Window {
    width: 480
    height: 480
    visible: true

    Rectangle {
        id: root
        anchors.fill: parent
        color: "black"


        RadarLine {
            id: radarLine
            x: 100
            y: 100
            width: 200
            height: 200
            color: "blue"
        }
    }
}
