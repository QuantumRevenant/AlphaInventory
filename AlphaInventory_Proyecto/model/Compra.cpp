#ifndef COMPRA_CPP
#define COMPRA_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Compra::Compra() {}
Compra::Compra(int _codCompra, int _codProveedor, int _codUsuario, double _monto, bool _estado):Procesos(_codUsuario, _monto, _estado)
{
    codCompra = _codCompra;
    codProveedor = _codProveedor;
}
Compra::~Compra() {}
int     Compra::getCodCompra()
{
    return codCompra;
}
int     Compra::getCodProveedor()
{
    return codProveedor;
}
void    Compra::setCodCompra(int _codCompra)
{
    codCompra = _codCompra;
}
void    Compra::setCodProveedor(int _codProveedor)
{
    codProveedor = _codProveedor;
}

#endif // COMPRA_CPP