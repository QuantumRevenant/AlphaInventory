#ifndef DVENTA_CPP
#define DVENTA_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

DVenta::DVenta() {}
DVenta::~DVenta() {}
int     DVenta::getCodVenta()
{
    return codVenta;
}
void    DVenta::setCodVenta(int _codVenta)
{
    codVenta = _codVenta;
}

#endif // DVENTA_CPP