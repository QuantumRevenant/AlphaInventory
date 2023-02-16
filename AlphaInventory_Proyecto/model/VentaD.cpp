#ifndef VENTAD_CPP
#define VENTAD_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

VentaD::VentaD() {}
VentaD::VentaD(int _codVenta, int _codProducto, int _cantidad, double _precio):ProcesosD(_codProducto, _cantidad, _precio)
{
    codVenta = _codVenta;
}
VentaD::~VentaD() {}
int     VentaD::getCodVenta()
{
    return codVenta;
}
void    VentaD::setCodVenta(int _codVenta)
{
    codVenta = _codVenta;
}

#endif // VENTAD_CPP