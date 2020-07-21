import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.0

import CalcLogic 1.0

Window {
    visible: true
    width: 350
    height: 450
    title: qsTr("QtCalculator")
    color: "#f1c27d"

    CalcLogic {
        id: calculatorLogic
    }

    GridLayout {
        anchors.fill: parent
        columnSpacing: 0;
        rowSpacing: 0;
        columns: 4;

        Rectangle {
            id: resultBox
            Layout.row: 0;
            Layout.column: 0;
            Layout.columnSpan: 4
            Layout.fillWidth: true
            height: 90
            border.width: 2;
            border.color: "red";

            Text {
                anchors.fill: parent
                id: resultText
                text: qsTr("")
                verticalAlignment: Text.AlignBottom
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 40
                anchors.margins: 5;
            }
        }

        Repeater {
            id: arithmeticOps
            model: ["/", "*", "+", "-"]
            CalcButton {
                Layout.column: index;
                Layout.row: 1;
                Layout.fillWidth: true;
                height: 60;
                textHeight: 30;
                text: modelData;
                Layout.margins: 5;
                onClicked: {
                    resultText.text = calculatorLogic.arithmeticOpsPressed(modelData);
                }
            }
        }

        Repeater {
            id: numbers
            model: ["7", "8", "9", "4", "5", "6", "1", "2", "3"]
            CalcButton {
                Layout.column: index % 3;
                Layout.row: 2 + (index / 3);
                Layout.fillWidth: true;
                height: 60;
                textHeight: 30;
                text: modelData;
                Layout.margins: 5;
                onClicked: {
                    resultText.text = calculatorLogic.onNumberPressed(modelData);
                }
            }
        }

        CalcButton {
            id: equals
            Layout.column: 3;
            Layout.row: 2;
            Layout.rowSpan: 4;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            textHeight: 30;
            text: "=";
            Layout.margins: 5;
            onClicked: {
                resultText.text = calculatorLogic.evaluateExpression();
            }
        }

        Repeater {
            id: otherOps
            model: ["0", ".", "C"]
            CalcButton {
                Layout.column: index;
                Layout.row: 5;
                Layout.fillWidth: true;
                height: 60;
                textHeight: 30;
                text: modelData;
                Layout.margins: 5;
                onClicked: {
                    resultText.text = calculatorLogic.onOtherOpsPressed(modelData);
                }
            }
        }
    }
}


/*##^##
Designer {
    D{i:5;invisible:true}
}
##^##*/
