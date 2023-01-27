#include <iostream>
#include <string>
#include <vector>
#include "../model/Usuario.cpp"
using namespace std;

/*

*/

int main(int argc, char *argv[])
{
    Usuario objUsuario;
    string test="test";
    cout<<test<<endl;
    cout<<objUsuario.encriptar(test)<<endl;
    cout<<objUsuario.desencriptar(objUsuario.encriptar(test))<<endl;
    return 0;
}
