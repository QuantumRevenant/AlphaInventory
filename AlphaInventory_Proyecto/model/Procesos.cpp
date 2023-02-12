#ifndef PROCESOS_CPP
#define PROCESOS_CPP
#include <iostream>
#include <string>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Procesos::Procesos() {}
Procesos::Procesos(int _codUsuario, double _monto, bool _estado)
{
    codUsuario = _codUsuario;
    monto = _monto;
    estado = _estado;
    fecha = currentDateTime();
}
Procesos::~Procesos() {}
int     Procesos::getCodUsuario
{
    return codUsuario;
}
string  Procesos::getFecha()
{
    return fecha;
}
double  Procesos::getMonto()
{
    return monto;
}
bool    Procesos::getEstado()
{
    return estado;
}
void    Procesos::setCodUsuario(int _codUsuario)
{
    codUsuario = _codUsuario;
}
void    Procesos::setFecha(string _fecha)
{
    fecha = _fecha;
}
void    Procesos::setMonto(double _monto)
{
    monto = _monto;
}
void    Procesos::setEstado(bool _estado)
{
    estado = _estado;
}
#endif // PROCESOS_CPP
