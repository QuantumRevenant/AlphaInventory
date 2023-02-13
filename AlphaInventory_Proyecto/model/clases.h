#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <vector>
#include "FuncionesGenerales.h"

using namespace std;

class Usuario;
class Procesos;
class Compra;
class Venta;
class ProcesosD;
class DCompra;
class DVenta;

#include "Usuario.h"

class Componente
{
private:
    string nombre;
    string cantidad;

public:
    Componente();
    Componente(string, string);
    ~Componente();
    string getNombre();
    string getCantidad();
    void setNombre(string);
    void setCantidad(string);
};

class Marca
{
private:
    int codigoMarca;
    string nombreMarca;

public:
    Marca();
    Marca(int, string);
    ~Marca();
    int getCodigoMarca();
    string getNombreMarca();
    void setCodigoMarca(int);
    void setNombreMarca(string);
};

class Producto
{
private:
    int codigo;
    string nombre;
    int numMarcas;
    vector<Marca> vectorMarcas;
    vector<float> precioUnitario;
    vector<int> stock;
    int numComponentes;
    vector<Componente> vectorComponentes;

public:
    Producto();
    Producto(string, vector<Componente> &, int);
    ~Producto();
    void setCodigo(int);
    void setNombre(string);
    void setNumComponentes(int);
    void setNumMarcas(int);
    void modifyPrecioUnitario(float, int);
    void modifyStock(int, int);
    int getCodigo();
    string getNombre();
    int getNumComponentes();
    int getNumMarcas();
    bool marcaRegistrada(int);
    int partition(int, int);
    void quickSort(int, int);
    void ordenarComponentes();
    void addComponente(Componente);
    void addMarca(Marca, float);
    void deleteComponente(int);
    void deleteMarca(int);
    Componente getComponente(int);
    Marca getMarca(int);
    float getPrecioUnitario(int);
    int getStock(int);
};

class Procesos
{
private:
    int codUsuario;
    string fecha;
    double monto;
    bool estado;

public:
    Procesos();
    Procesos(int, double, bool);
    ~Procesos();
    int getCodUsuario();
    string getFecha();
    double getMonto();
    bool getEstado();
    void setCodUsuario(int);
    void setFecha(string);
    void setMonto(double);
    void setEstado(bool);
};

class Compra : public Procesos
{
private:
    int codCompra;
    int codProveedor;

public:
    Compra();
    ~Compra();
    int getCodCompra();
    int getCodProveedor();
    void setCodCompra(int);
    void setCodProveedor(int);
};

class Venta : public Procesos
{
private:
    int codVenta;
    int codCliente;

public:
    Venta();
    ~Venta();
    int getcodVenta();
    int getCodCliente();
    void setCodVenta(int);
    void setCodCliente(int);
};

class ProcesosD
{
private:
    int codProducto;
    int cantidad;
    double precio;
    double monto;
    bool estado;

public:
    ProcesosD();
    ProcesosD(int, int, double, double, bool);
    ~ProcesosD();
    int getCodProducto();
    int getCantidad();
    double getPrecio();
    double getMonto();
    bool getEstado();
    void setCodProducto(int);
    void setCantidad(int);
    void setPrecio(double);
    void setMonto(double);
    void setEstado(bool);
};

class DCompra : public ProcesosD
{
private:
    int codCompra;

public:
    DCompra();
    ~DCompra();
    int getCodCompra();
    void setCodCompra(int);
};

class DVenta : public ProcesosD
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
