#include <iostream>
#include <string>
#include <vector>
#include "../controller/usuarioController.h"

usuarioController userController;

using namespace std;

/*

*/

int main(int argc, char *argv[])
{
    cout << "Here" << endl;
    system("pause");
    userController.archRecuperarDatos();
    cout << "Here" << endl;
    for (int i = 0; i < userController.size(); i++)
        cout << userController.get(i).getCodUsuario() << endl;
    cout<<userController.size();
    cout << "Here" << endl;
    userController.archGrabarDatos();
    return 0;
}