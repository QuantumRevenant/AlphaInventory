#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <string>
#include <vector>
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
    string  encriptar(string);
    string  desencriptar(string);
    string  getCodigo();
};

#endif // CLASES_H
