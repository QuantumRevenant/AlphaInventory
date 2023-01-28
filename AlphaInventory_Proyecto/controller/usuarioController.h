#ifndef USUARIOCONTROLLER_H
#define USUARIOCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "../model/Usuario.cpp"

class usuarioController
{
private:
    vector<Usuario> vectorUsuario;

public:
    usuarioController();
    void add(Usuario);
    Usuario get(int);
    void modify(Usuario, int);
    bool validarSesion(string, string); // nos valida si existe una sesión.
    Usuario getUsuario(string);         // nos devuelve el usuario por medio de su key. (censurar la contraseña).
    Usuario getUsuario(string, string); // nos devuelve el usuario por medio de su usuario y contraseña.
};

usuarioController::usuarioController() {}
void usuarioController::add(Usuario obj)
{
    vectorUsuario.push_back(obj);
}
Usuario usuarioController::get(int pos)
{
    return vectorUsuario[pos];
}
void usuarioController::modify(Usuario obj, int pos)
{
    vectorUsuario[pos] = obj;
}
bool usuarioController::validarSesion(string username, string contrasena)
{
    int index = -1,
        i = 0;
    bool found = false;
    while (i < vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getUsername() == username)
            found = true;
        i++;
    }
    if (found)
    {
        if (contrasena == vectorUsuario[i-1].desencriptar(vectorUsuario[i-1].getContrasena()))
            return true;
        else
            return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
    }
    else
        return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
}
Usuario usuarioController::getUsuario(string key)
{
    int i = 0;
    bool found = false;

    while (i < vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getCodigo() == key)
            found = true;
        i++;
    }
    Usuario objSalida = vectorUsuario[i-1];
    objSalida.setContrasena("********");
    return objSalida;
}
Usuario usuarioController::getUsuario(string username, string contrasena)
{
    int i = 0;
    bool found = false;
    if (!validarSesion(username, contrasena))
    {
        Usuario objInvalido;
        return objInvalido;
    }
    else
    {
        while (i < vectorUsuario.size() && !found)
        {
            if (vectorUsuario[i].getUsername() == username)
                found = true;
            i++;
        }
        Usuario objSalida = vectorUsuario[i-1];
        objSalida.setContrasena("********");
        return objSalida;
    }
}
#endif