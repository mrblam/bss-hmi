import QtQuick 2.4

Item {
    width: 400
    height: 400

    Flickable {
        id: flickable
        x: 50
        y: 31
        width: 300
        height: 300

        Image {
            id: image
            x: 111
            y: 133
            width: 100
            height: 100
            source: "qrc:/qtquickplugin/images/template_image.png"
        }
    }
}
