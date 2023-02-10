#ifndef COMPONENTE_CPP
#define COMPONENTE_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Componente::Componente() {}
Componente::Componente(string _nombre, string _cantidad)
{
    nombre = _nombre;
    cantidad = _cantidad;
}
Componente::~Componente() {}
string  Componente::getNombre()
{
    return nombre;
}
string  Componente::getCantidad()
{
    return cantidad;
}
void    Componente::setNombre(string _nombre)
{
    nombre = _nombre;
}
void    Componente::setCantidad(string _cantidad)
{
    cantidad = _cantidad;
}

#endif // COMPONENTE_CPP