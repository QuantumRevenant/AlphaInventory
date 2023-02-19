#ifndef KARDEX_H
#define KARDEX_H

#include <iostream>
#include <string>

using namespace std;

/*

*/

class kardex
{
private:
    string fechaDeEmision;
    int cantidad;
    double montoUnitario;
    int codProducto;
    string codProceso;
    string comprobante;

    bool isSalida;
    string motivo;
    string observacion;

public:
    kardex();
    kardex(string, int, int,double, string, string, bool, string, string);
    ~kardex();

    string  getFechaDeEmision();
    int     getCantidad();
    double     getMontoUnitario();
    int     getCodProducto();
    string  getCodProceso();
    string  getComprobante();
    bool    getIsSalida();
    string  getMotivo();
    string  getObservacion();

    void    setFechaDeEmision(string);
    void    setCantidad(int);
    void    setMontoUnitario(double);
    void    setCodProducto(int);
    void    setCodProceso(string);
    void    setComprobante(string);
    void    setIsSalida(bool);
    void    setMotivo(string);
    void    setObservacion(string);
};

#endif