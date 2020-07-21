#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QObject>

class CalcLogic : public QObject
{
    Q_OBJECT
public:
    explicit CalcLogic(QObject *parent = nullptr) noexcept;
    virtual ~CalcLogic() noexcept;

    Q_INVOKABLE QString onNumberPressed( const QString inputNumber ) noexcept;
    Q_INVOKABLE QString ArithmeticOpsPressed( const QString inputOp ) noexcept;
    Q_INVOKABLE QString EvaluateExpression() noexcept;
    Q_INVOKABLE QString onDotPressed() noexcept;


private:
    static const unsigned char NO_OPERATION = 0;
    static const unsigned char ADD_OPERATION = 1;
    static const unsigned char SUBTRACT_OPERATION = 2;
    static const unsigned char MULTIPLY_OPERATION = 3;
    static const unsigned char DIVISION_OPERATION = 4;

    QString leftOperand;
    QString rightOperand;
    QString output;
    unsigned char operationType;

    void ResetAfterCalculation() noexcept;
    void updateOutput() noexcept;

signals:

};

#endif // CALCLOGIC_H
