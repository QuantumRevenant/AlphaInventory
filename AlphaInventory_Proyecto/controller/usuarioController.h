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
    bool validarUsuarioNoExiste(string);
    bool validarSesion(string, string); // nos valida si existe una sesión.
    int getUsuario(string, bool);
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
    string dataToSave = obj.getContrasena();
    if (dataToSave == "********")
        dataToSave = vectorUsuario[pos].getContrasena();
    vectorUsuario[pos] = obj;
    vectorUsuario[pos].setContrasena(dataToSave);
}
bool usuarioController::validarUsuarioNoExiste(string username)
{
    int i = 0;
    bool found = false;
    while (i < (int)vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getUsername() == username)
            found = true;
        i++;
    }
    return found;
}
bool usuarioController::validarSesion(string username, string contrasena)
{
    int i = 0;
    bool found = false;
    while (i < (int)vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getUsername() == username)
            found = true;
        i++;
    }
    if (found)
    {
        if (contrasena == vectorUsuario[i - 1].desencriptar(vectorUsuario[i - 1].getContrasena()))
            return true;
        else
            return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
    }
    else
        return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
}
int usuarioController::getUsuario(string key, bool a)
{
    int i = 0, index = 0;
    bool found = false;

    if(a)
        cout<<"";

    while (i < (int)vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getCodigo() == key)
        {
            found = true;
            index = i;
        }
        i++;
    }
    if (found)
        return index;
    else
        return -1;
}
Usuario usuarioController::getUsuario(string key)
{
    int i = 0;
    bool found = false;

    while (i < (int)vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getCodigo() == key)
            found = true;
        i++;
    }
    Usuario objSalida = vectorUsuario[i - 1];
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
        while (i < (int)vectorUsuario.size() && !found)
        {
            if (vectorUsuario[i].getUsername() == username)
                found = true;
            i++;
        }
        Usuario objSalida = vectorUsuario[i - 1];
        objSalida.setContrasena("********");
        return objSalida;
    }
}
#endif