#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Usuario
{
private:
    int codUsuario;
    string username;
    string nombre;
    string apellidos;
    string documento;
    int numDocumento;
    string contrasena;
    string tipoUsuario;

public:
    Usuario();
    ~Usuario();
    Usuario(int, string, string, string, string, string, int, string);
    void setCodUsuario(int);
    void setUsername(string);
    void setNombre(string);
    void setApellidos(string);
    void setDocumento(string);
    void setNumDocumento(int);
    void setContrasena(string);
    void setTipoUsuario(string);
    int getCodUsuario();
    string getUsername();
    string getNombre();
    string getApellidos();
    string getDocumento();
    int getNumDocumento();
    string getContrasena();
    string getTipoUsuario();
    void listarDatos();
};
/*
class Producto
{
private:
    string codigo;
    string nombre;
    float precioUnitario;
    int numComponentes;
    vector<Componente> vectorComponentes;

public:
    Producto();
    Producto(string, float, vector<Componente> &);
    ~Producto();
    void setCodigo(string);
    void setNombre(string);
    void setPrecioUnitario(float);
    void setNumComponentes(int);
    string getCodUsuario();
    string getNombre();
    float getPrecioUnitario();
    int getNumComponentes();
    int partition(int, int);
    void quickSort(int, int);
    void ordenarComponentes();
    void addComponente(Componente);
    void deleteComponente(int);
    Componente getComponente(int);
};
*/
class Marca
{
private:
    int codigoMarca;
    string nombreMarca;

public:
    Marca();
    Marca(int, string);
    ~Marca();
    int getCodUsuarioMarca();
    string getNombreMarca();
    void setCodigoMarca(int);
    void setNombreMarca(string);
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
    int getCodUsuario;
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

#endif // CLASES_H
