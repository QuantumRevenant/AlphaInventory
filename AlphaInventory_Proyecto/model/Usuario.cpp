#ifndef USUARIO_CPP
#define USUARIO_CPP
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

using namespace std;

Usuario::Usuario() {}
Usuario::~Usuario() {}
Usuario::Usuario(int _codUsuario,string _username, string _contrasena, string _nombre, string _apellidos, string _tipoDocumento, int _numDocumento, string _tipoUsuario)
{
    codUsuario=_codUsuario;
    username = _username;
    contrasena = _contrasena;
    nombre = _nombre;
    apellidos = _apellidos;
    tipoDocumento = _tipoDocumento;
    numDocumento = _numDocumento;
    tipoUsuario = _tipoUsuario;
}
void Usuario::setCodUsuario(int _codUsuario)
{
    codUsuario=_codUsuario;
}
void Usuario::setUsername(string _username)
{
    username = _username;
}
void Usuario::setNombre(string _nombre)
{
    nombre = _nombre;
}
void Usuario::setApellidos(string _apellidos)
{
    apellidos = _apellidos;
}
void Usuario::setDocumento(string _tipoDocumento)
{
    tipoDocumento = _tipoDocumento;
}
void Usuario::setNumDocumento(int _numDocumento)
{
    numDocumento = _numDocumento;
}
void Usuario::setContrasena(string _contrasena)
{
    contrasena = _contrasena;
}
void Usuario::setTipoUsuario(string _tipoUsuario)
{
    tipoUsuario = _tipoUsuario;
}
int Usuario::getCodUsuario()
{
    return codUsuario;
}
string Usuario::getUsername()
{
    return username;
}
string Usuario::getNombre()
{
    return nombre;
}
string Usuario::getApellidos()
{
    return apellidos;
}
string Usuario::getTipoDocumento()
{
    return tipoDocumento;
}
int Usuario::getNumDocumento()
{
    return numDocumento;
}
string Usuario::getContrasena()
{
    return contrasena;
}
string Usuario::getTipoUsuario()
{
    return tipoUsuario;
}
void Usuario::listarDatos()
{
    system("cls");
    cout<<"Codigo: "<<getCodUsuario()<<endl;
    cout << "Usuario: " << getUsername() << endl;
    cout << "Contraseña: " << getContrasena() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Apellidos: " << getApellidos() << endl;
    cout << "Tipo de usuario: " << getTipoUsuario() << endl;
    cout << "Tipo de documento: " << getTipoDocumento() << endl;
    cout << "Numero de documento: " << getNumDocumento() << endl;
    system("pause");
}
#endif