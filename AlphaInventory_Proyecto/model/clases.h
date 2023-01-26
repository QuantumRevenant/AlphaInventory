#if !defined(_CLASES_H_)
#define _CLASES_H_
#include <iostream>
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
    
};

#endif // _CLASES_H_
