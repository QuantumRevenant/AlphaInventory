#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Producto::Producto() {}
Producto::~Producto() {}
void Producto::setCodigo(string _codigo)
{
    codigo = _codigo;
}
void Producto::setNombre(string _nombre)
{
    nombre = _nombre;
}
void Producto::setPrecioUnitario(float _precioUnitario)
{
    precioUnitario = _precioUnitario;
}
void Producto::addCompuesto(Compuesto comp)
{
    compuestos.push_back(comp);
}
string Producto::getCodigo()
{
    return codigo;
}
string Producto::getNombre()
{
    return nombre;
}
float Producto::getPrecioUnitario()
{
    return precioUnitario;
}
Compuesto Producto::getCompuesto(int pos)
{
    return compuestos[pos];
}

#endif // PRODUCTO_H
