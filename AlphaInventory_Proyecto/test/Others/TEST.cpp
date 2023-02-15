#include <iostream>
#include <string>
#include <vector>
#include "../model/FuncionesGenerales.h"
using namespace std;

#define VOFFSET 5
#define HOFFSET 5

/*

*/

int main(int argc, char *argv[])
{
    doEndline(VOFFSET - 2);
    cout << doTab(HOFFSET, "") << "-------NO TENEMOS REGISTRO DE ADMINISTRADORES-------" << endl
         << doTab(HOFFSET, "") << "-REGISTRA UN NUEVO ADMINISTRADOR ANTES DE CONTINUAR-" << endl;
    return 0;
}