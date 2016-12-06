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

            sources: ["qrc:/images/red0.png",
                "qrc:/images/red1.png",
                "qrc:/images/red2.png",
                "qrc:/images/red3.png",
                "qrc:/images/red4.png",
                "qrc:/images/red5.png",
                "qrc:/images/red6.png",
                "qrc:/images/red7.png",
                "qrc:/images/red8.png",
                "qrc:/images/red9.png",
            ]
            index: 0
        }

        Timer {
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                ++radarLine.index;
                radarLine.index = radarLine.index % 10;
                console.log("Index: ", radarLine.index);
            }
        }

    }
}
