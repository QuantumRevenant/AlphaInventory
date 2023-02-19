#ifndef KARDEX_CPP
#define KARDEX_CPP

#include <iostream>
#include <string>
#include <vector>
#include "kardex.h"
#include "FuncionesGenerales.h"

using namespace std;

kardex::kardex()
{
}

kardex::kardex(string _fechaDeEmision, int _cantidad, int _codProducto, double _montoUnitario, string _codProceso, string _comprobante, bool _isSalida, string _motivo, string _observacion)
{
    fechaDeEmision = _fechaDeEmision;
    cantidad = _cantidad;
    montoUnitario=_montoUnitario;
    codProducto = _codProducto;
    codProceso = _codProceso;
    comprobante = _comprobante;
    isSalida = _isSalida;
    motivo = _motivo;
    observacion = _observacion;
}

kardex::~kardex()
{
}

string kardex::getFechaDeEmision() { return fechaDeEmision; }
int kardex::getCantidad() { return cantidad; }
double kardex::getMontoUnitario() { return montoUnitario; }
int kardex::getCodProducto() { return codProducto; }
string kardex::getCodProceso() { return codProceso; }
string kardex::getComprobante() { return comprobante; }
bool kardex::getIsSalida() { return isSalida; }
string kardex::getMotivo() { return motivo; }
string kardex::getObservacion() { return observacion; }

void kardex::setFechaDeEmision(string _fechaDeEmision) { fechaDeEmision = _fechaDeEmision; }
void kardex::setCantidad(int _cantidad) { cantidad = _cantidad; }
void kardex::setMontoUnitario(double _montoUnitario){montoUnitario=_montoUnitario;}
void kardex::setCodProducto(int _codProducto) { codProducto = _codProducto; }
void kardex::setCodProceso(string _codProceso) { codProceso = _codProceso; }
void kardex::setComprobante(string _comprobante) { comprobante = _comprobante; }
void kardex::setIsSalida(bool _isSalida) { isSalida = _isSalida; }
void kardex::setMotivo(string _motivo) { motivo = _motivo; }
void kardex::setObservacion(string _observacion) { observacion = _observacion; }

#endif