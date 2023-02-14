#ifndef TERCEROS_CPP
#define TERCEROS_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Terceros::Terceros() {}
Terceros::Terceros(string _nombre, string _tipoDocumento, string _documento)
{
    nombre = _nombre;
    tipoDocumento = _tipoDocumento;
    documento = _documento;
}
Terceros::~Terceros() {}
string Terceros::getNombre()
{
    return nombre;
}
string Terceros::getTipoDocumento()
{
    return tipoDocumento;
}
string Terceros::getDocumento()
{
    return documento;
}
void Terceros::setNombre(string _nombre)
{
    nombre = _nombre;
}
void Terceros::setTipoDocumento(string _tipoDocumento)
{
    tipoDocumento = _tipoDocumento;
}
void Terceros::setDocumento(string _documento)
{
    documento = _documento;
}

#endif // TERCEROS_CPP