#ifndef CAJACONTROLLER_H
#define CAJACONTROLLER_H
#include <iostream>

class CajaController
{
private:
    double saldo;

public:
    CajaController();
    CajaController(double);
    ~CajaController();
    void setSaldo(double);
    double getSaldo();
    void modifySaldo(double, bool);
};

CajaController::CajaController() {}
CajaController::CajaController(double _saldo)
{
    saldo = _saldo;
}
CajaController::~CajaController() {}
void CajaController::setSaldo(double _saldo)
{
    saldo = _saldo;
}
double CajaController::getSaldo()
{
    return saldo;
}
void CajaController::modifySaldo(double monto, bool operacion)
{
    if (operacion)
        saldo += monto;
    else
        saldo -= monto;
}

#endif // CAJACONTROLLER_H