#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <vector>
#include "estructuras.h"
using namespace std;


class Usuario
{
private:
    string  username;
    string  nombre;
    string  apellidos;
    string  documento;
    int     numDocumento;
    string  contrasena;
    string  tipoUsuario;

public:
    Usuario();
    ~Usuario();
    Usuario(string, string);//username y contraseña (capaz agregar string e int para hacer el codigo a futuro)
    Usuario(string,string,string,string,string,int,string);
    void    setUsername(string);
    void    setNombre(string);
    void    setApellidos(string);
    void    setDocumento(string);
    void    setNumDocumento(int);
    void    setContrasena(string);
    void    setTipoUsuario(string);
    string  getUsername();
    string  getNombre();
    string  getApellidos();
    string  getDocumento();
    int     getNumDocumento();
    string  getContrasena();
    string  getTipoUsuario();
    void    modifyUsername();
    void    modifyNombre();
    void    modifyApellidos();
    void    modifyDocumento();
    void    modifyContrasena();
    void    listarDatos();
    string  encriptar(string);
    string  desencriptar(string);
    string  getCodigo();
};

class Producto
{
private:
    string  codigo;
    string  nombre;
    float   precioUnitario;
    int     numCompuestos;
    vector<Compuesto> vectorCompuestos;

public:
    Producto();
    Producto(string, float, vector<Compuesto>&);
    ~Producto();
    void    setCodigo(string);
    void    setNombre(string);
    void    setPrecioUnitario(float);
    void    setNumCompuestos(int);
    string  getCodigo();
    string  getNombre();
    float   getPrecioUnitario();
    int     getNumCompuestos();
    int     partition(int, int);
    void    quickSort(int, int);
    void    ordenarCompuestos();
    void    addCompuesto(Compuesto);
    void    deleteCompuesto(int);
    Compuesto getCompuesto(int);
};

class Marca
{
private:
    int     codigoMarca;
    string  nombreMarca;
public:
    Marca();
    Marca(int,string);
    ~Marca();
    int     getCodigoMarca();
    string  getNombreMarca();
    void    setCodigoMarca(int);
    void    setNombreMarca(string);
};
class Procesos
{
private:
    int     codUsuario;
    string  fecha;
    double  monto;
    bool    estado;
public:
    Procesos();
    Procesos(int,double, bool);
    ~Procesos();
    int     getCodUsuario();
    string  getFecha();
    double  getMonto();
    bool    getEstado();
    void    setCodUsuario(int);
    void    setFecha(string);
    void    setMonto(double);
    void    setEstado(bool);
};

class Compra: public Procesos
{
private:
    int     codCompra;
    int     codProveedor;
public:
    Compra();
    ~Compra();
    int     getCodCompra();
    int     getCodProveedor();
    void    setCodCompra(int);
    void    setCodProveedor(int);
};

class Venta: public Procesos
{
private:
    int     codVenta;
    int     codCliente;
public:
    Venta();
    ~Venta();
    int     getcodVenta();
    int     getCodCliente();
    void    setCodVenta(int);
    void    setCodCliente(int);
};

class ProcesosD
{
private:
    int     codProducto;
    int     cantidad;
    double  precio;
    double  monto;
    bool    estado;

public:
    ProcesosD();
    ProcesosD(int, int, double, double, bool);
    ~ProcesosD();
    int     getCodProducto();
    int     getCantidad();
    double  getPrecio();
    double  getMonto();
    bool    getEstado();
    void    setCodProducto(int);
    void    setCantidad(int);
    void    setPrecio(double);
    void    setMonto(double);
    void    setEstado(bool);
};

class DCompra: public ProcesosD
{
private:
    int codCompra;

public:
    DCompra();
    ~DCompra();
    int getCodCompra();
    void setCodCompra(int);
};

class DVenta: public ProcesosD
{
private:
    int codVenta;

public:
    DVenta();
    ~DVenta();
    int getCodVenta();
    void setCodVenta(int);
};

#endif // CLASES_H
