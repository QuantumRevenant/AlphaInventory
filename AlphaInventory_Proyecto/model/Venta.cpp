#ifndef VENTA_CPP
#define VENTA_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Venta::Venta() {}
Venta::Venta(int _codVenta, int _codCliente, int _codUsuario, double _monto, bool _estado):Procesos(_codUsuario, _monto, _estado)
{
    codVenta = _codVenta;
    codCliente = _codCliente;
}
Venta::~Venta() {}
int     Venta::getCodVenta()
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