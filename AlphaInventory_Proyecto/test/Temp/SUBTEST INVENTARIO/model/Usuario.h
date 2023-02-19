#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

*/

class Usuario
{
private:
    int codUsuario;
    string username;
    string nombre;
    string apellidos;
    string tipoDocumento;
    long int numDocumento;
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
    string getTipoDocumento();
    int getNumDocumento();
    string getContrasena();
    string getTipoUsuario();
    
    void listarDatos();
};

#endif