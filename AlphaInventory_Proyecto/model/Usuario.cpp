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
void Usuario::modifyDocumento()
{
    int opt;
    int docSize;
    string _documento;
    do
    {
        system("cls");
        cout << "--TIPO DE DOCUMENTO---------" << endl;
        cout << "--DNI--------------------[1]" << endl;
        cout << "--CARNET EXT-------------[2]" << endl;
        cout << "--PASAPORTE--------------[3]" << endl;
        cout << "--RUC--------------------[4]" << endl;
        getValue("Ingrese opcion[1-4]: ", &opt);
        switch (opt)
        {
        case 1:
            _documento = "DNI";
            docSize = 8;
            break;
        case 2:
            _documento = "CE";
            docSize = 12;
            break;
        case 3:
            _documento = "PASAPORTE";
            docSize = 12;
            break;
        case 4:
            _documento = "RUC";
            docSize = 11;
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
        }
    } while (opt != 1 && opt != 2 && opt != 3 && opt != 4);
    string strInput = "0";
    do
    {
        system("cls");
        cout << getDocumento() << endl;
        if (!esNumero(strInput))
        {
            cout << "===[INTRODUCE UN VALOR NUMERICO]===" << endl;
        }
        getValue("Numero de documento: ", &strInput);
        if (strInput.size() != docSize)
        {
            cout << "Los documentos tipo " << documento << " deben contener " << docSize << " digitos" << endl;
            cout << "VUELVA A INGRESAR SU NUMERO DE DOCUMENTO" << endl;
            system("pause");
        }
    } while (!esNumero(strInput) || strInput.size() != docSize);

    if (confirmar("que su documento sea " + _documento + "con el N° " + strInput))
    {
        setDocumento(_documento);
        setNumDocumento(stoi(strInput));
    }
}
void Usuario::modifyContrasena()
{
    string contrasenaConfi;
    string _contrasena;
    do
    {
        cout << "###Para Cancelar digite 'CANCELAR'###" << endl
             << endl;
        system("cls");
        getValue("Contrasena(minimo 8 caracteres): ", &_contrasena);
        if (aMayuscula(contrasena) != "CANCELAR")
        {
            system("cls");
            getValue("Confirmar contrasena: ", &contrasenaConfi);
        }
        if (aMayuscula(contrasena) != "CANCELAR" && aMayuscula(contrasenaConfi) != "CANCELAR")
        {
            if (_contrasena.size() < 8)
            {
                cout << "La contrasena debe tener minimo 8 caracteres" << endl;
                cout << "VUELVA A INGRESAR UNA CONTRASENA" << endl;
                system("pause");
            }
            else if (_contrasena != contrasenaConfi)
            {
                cout << "Las contrasenas no son iguales" << endl;
                cout << "VUELVA A INGRESAR UNA CONTRASENA" << endl;
                system("pause");
            }
        }
    } while (_contrasena != contrasenaConfi || _contrasena.length() < 8 || !(aMayuscula(contrasena) != "CANCELAR" && aMayuscula(contrasenaConfi) != "CANCELAR"));
    if (aMayuscula(contrasena) != "CANCELAR" && aMayuscula(contrasenaConfi) != "CANCELAR")
        setContrasena(encriptar(_contrasena));
}
void Usuario::listarDatos()
{
    system("cls");
    cout << "Usuario: " << getUsername() << endl;
    cout << "Contraseña: " << getContrasena() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Apellidos: " << getApellidos() << endl;
    cout << "Tipo de usuario: " << getTipoUsuario() << endl;
    cout << "Tipo de documento: " << getDocumento() << endl;
    cout << "Numero de documento: " << getNumDocumento() << endl;
    system("pause");
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
        cout << "ERROR: DESENCRIPTACIÓN, RANGOS NO VÁLIDOS: " << a << endl;
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