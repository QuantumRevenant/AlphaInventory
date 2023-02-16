#ifndef COMPRAD_CPP
#define COMPRAD_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

CompraD::CompraD() {}
CompraD::CompraD(int _codCompra, int _codProducto, int _cantidad, double _precio):ProcesosD(_codProducto, _cantidad, _precio)
{
    codCompra = _codCompra;
}
CompraD::~CompraD() {}
int     CompraD::getCodCompra()
{
    return codCompra;
}
void    CompraD::setCodCompra(int _codCompra)
{
    codCompra = _codCompra;
}

#endif // COMPRAD_CPP