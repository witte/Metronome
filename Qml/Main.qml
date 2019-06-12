import QtQuick 2.12
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window
{
    id: window
    visible: true
    width: 260
    height: 336
    title: "Metronome"

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

        property int    currentBlock: 1
        property double currentBlockMultiplier: 1
        property double lastBlockY: 0
        property double lastBlockBpm: 120

        onPressed:
        {
            isDragging = false

            lastBlockY = mouse.y
            lastBlockBpm = metronome.bpm

            currentBlock = -1
        }

        onPositionChanged:
        {
            isDragging = true

            if (mouse.x <= block1)
            {
                currentBlock = 1
                lastBlockY = mouse.y
                lastBlockBpm = (max - ((max - min) * mouse.y / height)).toFixed (0)
                currentBlockMultiplier = 1

                metronome.bpm = lastBlockBpm
            }
            else
            {
                let curBlock = (mouse.x <= block2)? 2 : 3

                if (curBlock !== currentBlock)
                {
                    currentBlock = curBlock
                    lastBlockY = mouse.y
                    lastBlockBpm = metronome.bpm
                    currentBlockMultiplier = (currentBlock === 2)? 1 : 0.1
                }

                metronome.bpm = lastBlockBpm + (Number ( (10 * (lastBlockY - mouse.y) / height).toFixed (0) ) * currentBlockMultiplier)
            }
        }

        onReleased: if (!isDragging) metronome.isPlaying = !metronome.isPlaying

        onWheel: metronome.bpm += Number ( (wheel.pixelDelta.y * -0.05).toFixed (1) )

        Text
        {
            id: txtBpm
            anchors.horizontalCenter: parent.horizontalCenter
            text: metronome.bpm.toFixed (2)
            color: "#fff"
            font.bold: true
            font.pixelSize: 33
        }
    }

    Component.onCompleted: metronome.click.connect (function() { anmClick.restart() })
}
