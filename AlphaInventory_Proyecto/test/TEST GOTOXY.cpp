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

    system("cls");
            dibujarCuadro();
            centrarTexto("Iniciando Sesión",0,true,true,-3);
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                cout.flush();
                sleep(1);
            }
    // if (menuConfirmar("Desea cancelar los cambios", "Se perderan permanentemente"))
    //             menuError({"Cancelando los cambios..."});
    // vector<string> opt = {"Nombre de Usuario", "Nombres", "Apellidos"};

    // vector<string> answ;
    // menuDatos({"Contrasena", "Repetir Contrasena"}, answ,2,1);;
    // system("pause");
    // system("cls");
    // for (string x : answ)
    // {
    //     cout << x << endl;
    // }
}