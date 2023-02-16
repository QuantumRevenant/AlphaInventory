#ifndef PROCESOSD_CPP
#define PROCESOSD_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

ProcesosD::ProcesosD() {}
ProcesosD::ProcesosD(int _codProducto, int _cantidad, double _precio)
{
    codProducto = _codProducto;
    cantidad = _cantidad;
    precio = _precio;
    monto = precio * cantidad;
}
ProcesosD::~ProcesosD() {}
int     ProcesosD::getCodProducto()
{
    return codProducto;
}
int     ProcesosD::getCantidad()
{
    return cantidad;
}
double  ProcesosD::getPrecio()
{
    return precio;
}
double  ProcesosD::getMonto()
{
    return monto;
}
void    ProcesosD::setCodProducto(int _codProducto)
{
    codProducto = _codProducto;
}
void    ProcesosD::setCantidad(int _cantidad)
{
    cantidad = _cantidad;
}
void    ProcesosD::setPrecio(double _precio)
{
    precio = _precio;
}
void    ProcesosD::setMonto(double _monto)
{
    monto = _monto;
}

#endif // PROCESOSD_CPP