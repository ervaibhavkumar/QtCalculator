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
QString CalcLogic::onOtherOpsPressed(const QString input) noexcept {
    if (input == "0") return onNumberPressed(input);
    else if (input == ".") return onDotPressed();
    else {
        Q_ASSERT(input == "C");
        ResetAfterCalculation();
        return output;
    }
}

QString CalcLogic::evaluateExpression() noexcept {
    if (leftOperand.length() < 1 || operationType == NO_OPERATION || rightOperand.length() < 1) return output;

    const double val1 = leftOperand.toDouble();
    const double val2 = rightOperand.toDouble();

    switch (operationType) {
        case ADD_OPERATION: {
            const auto result = val1 + val2;
            output = QString::number(result);
            break;
        }
        case SUBTRACT_OPERATION: {
            const auto result = val1 - val2;
            output = QString::number(result);
            break;
        }
        case MULTIPLY_OPERATION: {
            const auto result = val1 * val2;
            output = QString::number(result);
            break;
        }
        default: {
            Q_ASSERT(operationType == DIVISION_OPERATION);
            if (val2 == 0.0) {
                output = "Invalid expression";
            }
            else {
                const auto result = val1 / val2;
                output = QString::number(result);
                break;
            }
        }
    }
    calculationDone();
    return output;
}

QString CalcLogic::onDotPressed() noexcept {
    if (operationType == NO_OPERATION) {
        if (leftOperand.length() < 1) {
            leftOperand.push_back("0.");
        }
        else {
            if (!leftOperand.contains(".")) {
                leftOperand.push_back(".");
            }
        }
    }
    else {
        if (rightOperand.length() < 1) {
            rightOperand.push_back("0.");
        }
        else {
            if (!rightOperand.contains(".")) {
                rightOperand.push_back(".");
            }
        }
    }
    updateOutput();
    return output;
}

void CalcLogic::ResetAfterCalculation() noexcept {
    leftOperand = rightOperand = output = "";
    operationType = NO_OPERATION;
}

void CalcLogic::calculationDone() noexcept {
    leftOperand = rightOperand = "";
    operationType = NO_OPERATION;
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
        output = "";
    }
}
