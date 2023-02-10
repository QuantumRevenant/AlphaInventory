#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../model/FuncionesGenerales.h"

using namespace std;

/*

*/

int main(int argc, char *argv[])
{
    vector<string> opt = {"Nombre de Usuario", "Nombres", "Apellidos"};
    vector<string> answ;
    menuDatos(opt,answ,1,1,"");;
    system("pause");
    system("cls");
    for (string x : answ)
    {
        cout << x << endl;
    }
}