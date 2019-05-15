import QtQuick 2.12
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window
{
    id: window
    visible: true
    width: 260
    height: 480
    title: "Metronome!"

    color: "#1A5FB4"

    Rectangle
    {
        id: blockBpm
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width / 3
        height: parent.height * ((metronome.bpm - metronome.minBpm) / (metronome.maxBpm - metronome.minBpm))

        color: "#164e93"
    }

    Rectangle
    {
        id: rightCorner
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width / 3

        color: "#1b69c5"
    }

    Rectangle
    {
        anchors.top: parent.top
        anchors.right: rightCorner.left
        anchors.bottom: parent.bottom
        width: parent.width / 3

        color: "#1661c0"
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#99C1F1"

        opacity: 0

        NumberAnimation on opacity
        {
            id: anmClick

            easing.type: Easing.OutQuart

            from: 0.5
            to: 0

            duration: 60 / metronome.bpm * 1000
        }
    }

    MouseArea
    {
        id: mouseArea

        anchors.fill: parent

        property double min: metronome.minBpm
        property double max: metronome.maxBpm

        property bool isDragging: false

        property double block1: width / 3
        property double block2: block1 * 2

        property int lastBlock: 1
        property double lastBlockY: 0
        property double lastBlockBpm: 120
        property double lastBlockMultiplier: 1

        onPressed:
        {
            lastBlockY = mouse.y

            if (mouse.x <= block1)
            {
                lastBlock = 1
                lastBlockMultiplier = 1
            }
            else if (mouse.x <= block2)
            {
                lastBlock = 2
                lastBlockMultiplier = 1
            }
            else
            {
                lastBlock = 3
                lastBlockMultiplier = 0.1
            }
        }

        onPositionChanged:
        {
            isDragging = true

            if (mouse.x <= block1)
            {
                lastBlock = 1
                lastBlockY = mouse.y
                lastBlockBpm = (max - ((max - min) * mouse.y / height)).toFixed (0)
                lastBlockMultiplier = 1

                metronome.bpm = lastBlockBpm
            }
            else //if (mouse.x <= block2)
            {
                let currentBlock = (mouse.x <= block2)? 2 : 3

                if (currentBlock !== lastBlock)
                {
                    lastBlockY = mouse.y
                    lastBlockBpm = metronome.bpm
                    lastBlock = currentBlock
                    lastBlockMultiplier = (currentBlock === 2)? 1 : 0.1
                }

                metronome.bpm = lastBlockBpm + (Number ( (10 * (lastBlockY - mouse.y) / height).toFixed (0) ) * lastBlockMultiplier)
            }
       }

        onReleased:
        {
            if (!isDragging) metronome.isPlaying = !metronome.isPlaying

            isDragging = false

            lastBlock = 1
            lastBlockBpm = metronome.bpm
        }

        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            text: metronome.bpm.toFixed (2)
            color: "#fff"
            font.family: "Mono"
            font.bold: true
            font.pointSize: 16
        }
    }

    Component.onCompleted: metronome.click.connect (function() { anmClick.restart() })
}
