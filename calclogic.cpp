#include "calclogic.h"

CalcLogic::CalcLogic(QObject *parent) noexcept : QObject(parent),
    leftOperand(""),
    rightOperand(""),
    output(""),
    operationType(NO_OPERATION) {}

CalcLogic::~CalcLogic() noexcept = default;

QString CalcLogic::onNumberPressed(const QString inputNumber) noexcept {
    if (operationType != NO_OPERATION) {
        leftOperand.append(inputNumber);
    }
    else {
        rightOperand.append(inputNumber);
    }
    updateOutput();
    return output;
}

QString CalcLogic::ArithmeticOpsPressed(const QString inputOp) noexcept {
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

    if (leftOperand.size() > 0) {
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

    if (rightOperand.size() > 0) {
        output += rightOperand;
    }

    if (output.size() < 1) {
        output = "0";
    }
}
