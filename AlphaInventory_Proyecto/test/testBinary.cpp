#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "../controller/usuarioController.h"
using namespace std;
usuarioController userController;

int main(int argc, char const *argv[])
{
    vector<Usuario> usuarios;

    for (int i = 0; i < userController.size(); i++)
        usuarios.push_back(userController.get(i));
    userController.archGrabarDatos();
    userController.archRecuperarDatos();
    vector<Usuario> usuariosRecuperados;
    for (int i = 0; i < userController.size(); i++)
        usuariosRecuperados.push_back(userController.get(i));
    for (Usuario usuario : usuariosRecuperados)
    {
        cout << "Tipo de documento: " << usuario.getTipoDocumento() << endl;
        cout << "Numero de documento: " << usuario.getNumDocumento() << endl;
        cout << "Nombre de usuario: " << usuario.getUsername() << endl;
        cout << "Contraseña: " << usuario.getContrasena() << endl;
        cout << "Nombre: " << usuario.getNombre() << endl;
        cout << "Apellidos: " << usuario.getApellidos() << endl;
        cout << "Tipo de usuario: " << usuario.getTipoUsuario() << endl;
        cout << "Codigo de usuario: " << usuario.getCodUsuario() << endl;
        cout << endl;
    }
    system("pause");
    return 0;
}
