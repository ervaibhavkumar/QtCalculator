#include <QDebug>

#include "calclogic.h"

CalcLogic::CalcLogic(QObject *parent) noexcept : QObject(parent),
    leftOperand(""),
    rightOperand(""),
    output(""),
    operationType(NO_OPERATION) {}

CalcLogic::~CalcLogic() noexcept = default;

QString CalcLogic::onNumberPressed(const QString inputNumber) noexcept {
    if (operationType == NO_OPERATION) {
        leftOperand.push_back(inputNumber);
    }
    else {
        rightOperand.push_back(inputNumber);
    }
    updateOutput();
    return output;
}

QString CalcLogic::arithmeticOpsPressed(const QString inputOp) noexcept {
    if (leftOperand.length() >= 1) {
        if (operationType == NO_OPERATION) {
            if (inputOp == "+") operationType = ADD_OPERATION;
            else if (inputOp == "-") operationType = SUBTRACT_OPERATION;
            else if (inputOp == "*") operationType = MULTIPLY_OPERATION;
            else {
                Q_ASSERT(inputOp == "/");
                operationType = DIVISION_OPERATION;
            }
        }
        updateOutput();
    }
    return output;
}

QString CalcLogic::EvaluateExpression() noexcept {
    return output;
}

QString CalcLogic::onDotPressed() noexcept {
    return output;
}

void CalcLogic::ResetAfterCalculation() noexcept {

}

void CalcLogic::updateOutput() noexcept {
    output = "";

    if (leftOperand.length() > 0) {
        output += leftOperand;
    }

    if (operationType != NO_OPERATION) {
        switch (operationType) {
        case ADD_OPERATION: {
            output += " + ";
            break;
        }
        case SUBTRACT_OPERATION: {
            output += " - ";
            break;
        }
        case MULTIPLY_OPERATION: {
            output += " * ";
            break;
        }
        default: {
            Q_ASSERT(operationType == DIVISION_OPERATION);
            output += " / ";
            break;
        }
        }
    }

    if (rightOperand.length() > 0) {
        output += rightOperand;
    }

    if (output.length() < 1) {
        output = "0";
    }
}
