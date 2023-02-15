#include <iostream>
#include <string>
#include <vector>
#include "../controller/Encrypter/sha256.cpp"
#include "../controller/controllers.h"

using namespace std;

/*

*/

usuarioController userController;

int main(int argc, char *argv[])
{
    string contra;
    cin>>contra;
    cout<<endl<<sha256(contra)<<endl<<userController.getUsuario(0).getContrasena()<<endl<<(sha256(contra)==userController.getUsuario(0).getContrasena());
    return 0;
}