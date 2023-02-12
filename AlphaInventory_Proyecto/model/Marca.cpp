#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
#include <string>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Marca::Marca() {}
Marca::Marca(int cod, string _nombreMarca)
{
    codigoMarca = cod;
    nombreMarca = _nombreMarca;
}
Marca::~Marca() {}
int     Marca::getCodUsuarioMarca()
{
    return codigoMarca;
}
string  Marca::getNombreMarca()
{
    return nombreMarca;
}
void    Marca::setCodigoMarca(int cod)
{
    codigoMarca = cod;
}
void    Marca::setNombreMarca(string _nombreMarca)
{
    nombreMarca = _nombreMarca;
}
#endif // PRODUCTO_H
