#ifndef USUARIO_CPP
#define USUARIO_CPP
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Clases.h"

using namespace std;

Usuario::Usuario() {}
Usuario::~Usuario() {}
Usuario::Usuario(string _username, string _contrasena)
{
    documento = "null";
    numDocumento = 999999999;
    username = _username;
    contrasena = _contrasena;
}

Usuario::Usuario(string _username, string _contrasena, string _nombre, string _apellidos, string _documento, int _numDocumento, string _tipoUsuario)
{
    username = _username;
    contrasena = _contrasena;
    nombre = _nombre;
    apellidos = _apellidos;
    documento = _documento;
    numDocumento = _numDocumento;
    tipoUsuario = _tipoUsuario;
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
void Usuario::setDocumento(string _documento)
{
    documento = _documento;
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
string Usuario::getDocumento()
{
    return documento;
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
string Usuario::encriptar(string dato)
{
    int valor = rand() % 9;
    string salida = "";
    if (valor <= 0 || valor >= 10)
        valor = 9;
    char referencia = valor + 96;
    salida = referencia + dato;
    for (int i = 1; i < salida.length(); i++)
        salida[i] = salida[i] + valor;
    return salida;
}
string Usuario::desencriptar(string dato)
{
    char a = dato[0];
    if (a < 96 || a > 122)
        cout << "ERROR: DESENCRIPTACIÓN, RANGOS NO VÁLIDOS: " <<a<< endl;
    else if (a == 96)
        cout << "ERROR: DESENCRIPTACIÓN, ENCRIPTACIÓN NULA" << endl;
    int valor = (int)a - 96;
    string salida = dato.erase(0, 1);
    for (int i = 0; i < salida.length(); i++)
        salida[i] = salida[i] - valor;
    return salida;
}
string Usuario::getCodigo()
{
    string codigo = documento + to_string(numDocumento);
    return codigo;
}
#endif