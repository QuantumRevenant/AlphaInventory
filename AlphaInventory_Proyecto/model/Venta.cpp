#ifndef VENTA_CPP
#define VENTA_CPP
#include <iostream>
#include <string>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Venta::Venta() {}
Venta::~Venta() {}
int     Venta::getcodVenta()
{
    return codVenta;
}
int     Venta::getCodCliente()
{
    return codCliente;
}
void    Venta::setCodVenta(int _codVenta)
{
    codVenta = _codVenta;
}
void    Venta::setCodCliente(int _codCliente)
{
    codCliente = _codCliente;
}
#endif // VENTA_CPP