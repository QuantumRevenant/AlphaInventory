#include <iostream>
#include <vector>
#include "../model/usuario.h"

class usuarioController
{
private:
    vector<Usuario> vectorUsuario;

public:
    usuarioController();
    void    add(Usuario);
    Usuario get(int);
    void    modify(int);
};

usuarioController::usuarioController() {
}
void    usuarioController::add(Usuario obj) {
    vectorUsuario.push_back(obj);
}
Usuario usuarioController::get(int pos) {
    return vectorUsuario[pos];
}
void    usuarioController::modify(int pos) {
    
}