#ifndef DCOMPRA_CPP
#define DCOMPRA_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

DCompra::DCompra() {}
DCompra::~DCompra() {}
int     DCompra::getCodCompra()
{
    return codCompra;
}
void    DCompra::setCodCompra(int _codCompra)
{
    codCompra = _codCompra;
}

#endif // DCOMPRA_CPP