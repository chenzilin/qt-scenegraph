import QtQuick 2.5
import QtQuick.Window 2.2
import Trapezium 1.0

Window {
    width: 480
    height: 480
    visible: true

    Rectangle {
        id: root
        anchors.fill: parent
        color: "black"

//        PathView {
//            id: pathView
//            anchors.fill: parent
//            model: myModel
//            delegate: myDelegate
//            pathItemCount: 3
//            interactive: true
//            preferredHighlightBegin: 0.5
//            preferredHighlightEnd: 0.5
//            highlightMoveDuration: 200
//            //highlightRangeMode: PathView.StrictlyEnforceRange

//            path: Path {
//                startX: -10; startY: 183

//                PathAttribute { name: "rotateY"; value: -80 }    // Y轴旋转角度
//                PathAttribute { name: "iconOpacity"; value: 0.5 }
//                PathAttribute { name: "iconScale"; value: 0.7 }

//                PathLine { x: 280; y: 183 }

//                PathAttribute { name: "rotateY"; value: 0 }    // Y轴旋转角度
//                PathAttribute { name: "iconOpacity"; value: 1.0 }
//                PathAttribute { name: "iconScale"; value: 1.0 }

//                PathLine { x: 315; y: 183 }

//                PathAttribute { name: "rotateY"; value: 150 }    // Y轴旋转角度
//                PathAttribute { name: "iconOpacity"; value: 0.4 }
//                PathAttribute { name: "iconScale"; value: 0.5 }
//            }
//        }
//        Component {
//            id: myDelegate
//            Item {
//                id: myImage

//                property real tempAngle: typeof PathView.rotateY === "undefined" ? 0.0 : PathView.rotateY

//                width: 35
//                height: 61
//                scale: typeof PathView.iconScale === "undefined" ? 1.0 : PathView.iconScale
//                opacity: typeof PathView.iconOpacity === "undefined" ? 1.0 : PathView.iconOpacity
//                transform: Rotation{ origin.x: 27.5; origin.y: 30.5; axis { x: 0; y: 100; z: 0 } angle: tempAngle }
//                Trapezium {
//                    width:100
//                    height:100
//                    src: icon
//                    rate:0.6
//                    direction:typeof PathView.rotateY<=0?"left":"right"
//                }
//            }
//        }

//        ListModel {
//            id: myModel
//            ListElement { name: "PGear"; icon: "qrc:/images/texture.png" }
//            ListElement { name: "RGear"; icon: "qrc:/images/texture.png" }
//            ListElement { name: "NGear"; icon: "qrc:/images/texture.png" }
//        }

        Trapezium {
            id: trapezium
            x: 80
            y: 80
            width: 300
            height: 300
            scale: 1.0
            rate: 1.0
            direction: Trapezium.Right
            partNum: 1000
            src: "qrc:/images/texture.png"

            SequentialAnimation on rate {
                NumberAnimation { to: 0.0; duration: 1000 }
                NumberAnimation { to: 1.0; duration: 1000 }
                loops: Animation.Infinite
            }
        }
    }
}
