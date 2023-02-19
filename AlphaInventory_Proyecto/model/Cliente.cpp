#ifndef CLIENTE_CPP
#define CLIENTE_CPP
#include <iostream>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Cliente::Cliente() {}
Cliente::Cliente(int _codCliente, string _nombre, long long int _documento): Terceros(_nombre, "DNI", _documento)
{
    codCliente = _codCliente;
}
Cliente::~Cliente() {}
void Cliente::setCodCliente(int _codCliente)
{
    codCliente = _codCliente;
}
int Cliente::getCodCliente()
{
    return codCliente;
}

#endif // CLIENTE_CPP