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
class CompraD;
class VentaD;
class Terceros;
class Cliente;
class Proveedor;

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
    Compra(int, int, int, double, bool);
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
    Venta(int, int, int, double, bool);
    ~Venta();
    int getCodVenta();
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
    ProcesosD(int, int, double, bool);
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

class CompraD : public ProcesosD
{
private:
    int codCompra;

public:
    CompraD();
    CompraD(int, int, int, double, bool);
    ~CompraD();
    int getCodCompra();
    void setCodCompra(int);
};

class VentaD : public ProcesosD
{
private:
    int codVenta;

public:
    VentaD();
    VentaD(int, int, int, double, bool);
    ~VentaD();
    int getCodVenta();
    void setCodVenta(int);
};

class Terceros
{
private:
    string nombre;
    string tipoDocumento;
    string documento;

public:
    Terceros();
    Terceros(string, string, string);
    ~Terceros();
    string getNombre();
    string getTipoDocumento();
    string getDocumento();
    void setNombre(string);
    void setTipoDocumento(string);
    void setDocumento(string);
};

class Cliente : public Terceros
{
private:
    int codCliente;

public:
    Cliente();
    Cliente(int, string, string);
    ~Cliente();
    void setCodCliente(int);
    int getCodCliente();
};
class Proveedor : public Terceros
{
private:
    int codProveedor;

public:
    Proveedor();
    Proveedor(int, string, string);
    ~Proveedor();
    void setCodProveedor(int);
    int getCodProveedor();
};

#endif // CLASES_H
