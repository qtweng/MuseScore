import QtQuick 2.12
import QtQuick.Controls 2.12

import MuseScore.NotationScene 1.0
import MuseScore.UiComponents 1.0
import MuseScore.Ui 1.0

Rectangle {
    id: root

    property alias orientation: gridView.orientation

    QtObject {
        id: privatesProperties

        property bool isHorizontal: orientation === Qt.Horizontal
    }

    GridViewSectional {
        id: gridView
        anchors.fill: parent

        sectionRole: "sectionRole"

        cellWidth: 36
        cellHeight: cellWidth

        model: noteInputModel

        sectionDelegate: SeparatorLine {
            orientation: gridView.orientation === Qt.Vertical ? Qt.Horizontal : Qt.Vertical
            visible: itemIndex !== 0
        }

        itemDelegate: FlatButton {
            property var item: Boolean(itemModel) ? itemModel : null
            property var hasSubitems: item.subitemsRole.length !== 0

            normalStateColor: Boolean(item) && item.checkedRole ? ui.theme.accentColor : "transparent"

            icon: Boolean(item) ? item.iconRole : IconCode.NONE
            hint: Boolean(item) ? item.hintRole : ""

            iconFont: ui.theme.toolbarIconsFont

            pressAndHoldInterval: 200

            width: gridView.cellWidth
            height: gridView.cellWidth

            onClicked: {
                if (menu.isOpened || (hasSubitems && !item.showSubitemsByPressAndHoldRole)) {
                    menu.toggleOpened()
                    return
                }

                Qt.callLater(noteInputModel.handleAction, item.codeRole)
            }

            onPressAndHold: {
                if (menu.isOpened || !hasSubitems) {
                    return
                }

                menu.toggleOpened()
            }

            StyledMenu {
                id: menu

                model: item.subitemsRole

                onHandleAction: {
                    Qt.callLater(noteInputModel.handleAction, actionCode, actionIndex)
                    menu.close()
                }
            }
        }
    }

    FlatButton {
        id: customizeButton

        anchors.margins: 8

        icon: IconCode.CONFIGURE
        normalStateColor: "transparent"

        onClicked: {
            api.launcher.open("musescore://notation/noteinputbar/customise")
        }
    }

    NoteInputBarModel {
        id: noteInputModel
    }

    Component.onCompleted: {
        noteInputModel.load()
    }

    states: [
        State {
            when: privatesProperties.isHorizontal
            PropertyChanges {
                target: gridView
                sectionWidth: 1
                sectionHeight: root.height
                rows: 1
                columns: gridView.noLimit
            }

            AnchorChanges {
                target: customizeButton
                anchors.right: root.right
                anchors.verticalCenter: root.verticalCenter
            }
        },
        State {
            when: !privatesProperties.isHorizontal
            PropertyChanges {
                target: gridView
                sectionWidth: root.width
                sectionHeight: 1
                rows: gridView.noLimit
                columns: 2
            }

            AnchorChanges {
                target: customizeButton
                anchors.bottom: root.bottom
                anchors.right: root.right
            }
        }
    ]
}
