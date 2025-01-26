import QtQuick
import QtWebEngine

Item {
    id: box

    /* database properties */
    property int block_id
    property int position
    property string content
    property string type
    property string language
    property string last_update

    /* customization properties */
    property color text_color
    property color background
    property var format
    property font font
    property int radius
    property var vertical_alignment
    property var horizontal_alignment

    Rectangle {
        color: box.background
        radius: box.radius
        anchors.fill: parent

        Loader {
            id: math
            anchors.centerIn: parent
            height: parent.height
            width: parent.width
            anchors.margins: 15
            active: box.language === 'math'
            sourceComponent: web_view
            onLoaded: {
                if (item)
                {
                    console.log("font size:", box.font.pixelSize);
                    console.log("background:", box.background);
                    console.log("color:", box.text_color);
                    console.log("content:", box.content);
                    console.log("")
                    item.content = box.content
                    item.text_color = box.text_color
                    item.background = box.background
                    item.font = box.font
                    item.background = box.background
                }
            }
        }

        TextEdit {
            id: text
            text: box.content
            font.family: box.font.family
            font.pixelSize: box.font.pixelSize
            color: box.text_color
            verticalAlignment: box.vertical_alignment
            horizontalAlignment: box.horizontal_alignment
            anchors.fill: parent
            anchors.margins: 15
            focus: false
            onContentSizeChanged: box.height = contentHeight + 30
            readOnly: true
            enabled: false

            visible: box.language !== 'math'

            wrapMode: box.type === 'Code' ? Text.WrapAnywhere : Text.WordWrap

            Component.onCompleted: {
                switch (box.type)
                {
                case 'Text': ;
                    text.textFormat = box.format ? box.format : TextEdit.MarkdownText
                    break
                case 'Code': ;
                    text.textFormat = TextEdit.PlainText
                    break
                default:
                    if (box.block_id > 0)
                    {
                        console.log('block_id:', box.block_id, 'does not have either of type Code or Text, assuming plain text.')
                    }
                    text.textFormat = TextEdit.PlainText
                }
            }
        }

        Component {
            id: web_view

            WebEngineView {
                id: web
                anchors.fill: parent

                property string content
                property color text_color
                property color background
                property font font
                property string html: String.raw`<!DOCTYPE html><html><head><script type="text/javascript" src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script></head><body style="margin: 0px; padding: 0px; font-size: %1px; text-align: center;"><div style="background-color: %2; color: %3; padding: 20px;">\[ %4 \]</div></body></html>`;

                Component.onCompleted: {
                    loadHtml(html.arg(web.font.pixelSize * 2).arg('#353535').arg('#f0f0f0').arg(web.content));
                }

                onLoadingChanged: function(info){
                    if (info.status === WebEngineView.LoadSucceededStatus)
                    {
                        runJavaScript("(() => { return { width: document.body.scrollWidth, height: document.body.scrollHeight}; })();", function(result) {
                            if (result)
                            {
                                box.width = result.width
                                box.height = result.height
                            }
                        });
                    }
                }
            }
        }
    }
}
