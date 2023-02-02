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
    int     stock;
    int     numCompuestos;
    vector<Compuesto> vectorCompuestos;

public:
    Producto();
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


#endif // CLASES_H
