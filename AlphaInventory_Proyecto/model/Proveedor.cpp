#ifndef PROVEEDOR_CPP
#define PROVEEDOR_CPP
#include <iostream>
#include "clases.h"
#include "../model/FuncionesGenerales.h"

Proveedor::Proveedor() {}
Proveedor::Proveedor(int _codProveedor, string _nombre, long long int _documento): Terceros(_nombre, "RUC", _documento)
{
    codProveedor = _codProveedor;
}
Proveedor::~Proveedor() {}
void Proveedor::setCodProveedor(int _codProveedor)
{
    codProveedor = _codProveedor;
}
int Proveedor::getCodProveedor()
{
    return codProveedor;
}

#endif // PROVEEDOR_CPP