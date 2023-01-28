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
    void    add(Usuario);
    Usuario get(int);
    void    modify(Usuario, int);
    bool    validarSesión(string,string);   //nos valida si existe una sesión.
    Usuario getUsuario(string);             //nos devuelve el usuario por medio de su key. (censurar la contraseña).
    Usuario getUsuario(string, string);     //nos devuelve el usuario por medio de su usuario y contraseña.

};

usuarioController::usuarioController()
{

}
void    usuarioController::add(Usuario obj)
{
    vectorUsuario.push_back(obj);
}
Usuario usuarioController::get(int pos)
{
    return vectorUsuario[pos];
}
void    usuarioController::modify(Usuario obj, int pos)
{
    vectorUsuario[pos]=obj;
}
#endif