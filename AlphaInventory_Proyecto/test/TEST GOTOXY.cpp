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
    int sizeY = 3, e = 0;
    string contrasena;
    string contrasenaConfi, strInput;

    do
    {
        sizeY = 3;
        e = 0;
        system("cls");
        dibujarCuadro();
        alinearXTexto("Contraseña: ", 0, true, 30, (-sizeY + e), true);
        e += 2;
        alinearXTexto("Repetir contraseña: ", 0, true, 30, (-sizeY + e), true);

        e = 0;
        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        strInput = enterContrasena();
        int size = strInput.size();
        contrasena = sha256(strInput);
        strInput = "";
        e += 2;

        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        contrasenaConfi = sha256(enterContrasena());
        e++;
        if (size < 8)
        {
            sizeY = 3;
            e = 0;
            system("cls");
            dibujarCuadro();
            system("color 4f");
            centrarTexto("~\t-La contrasena debe tener minimo 8 caracteres-\t~", 0, true, true, 0, (-sizeY + e));
            e += 2;
            centrarTexto("~\tVUELVA A INGRESAR UNA CONTRASENA\t~", 0, true, true, 0, (-sizeY + e));
            Sleep(1000);
            char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
            system(color);
        }
        else if (contrasena != contrasenaConfi)
        {
            sizeY = 3;
            e = 0;
            system("cls");
            dibujarCuadro();
            system("color 4f");
            centrarTexto("~\t-Las contrasenas no son iguales-\t~", 0, true, true, 0, (-sizeY + e));
            e += 2;
            centrarTexto("~\tVUELVA A INGRESAR UNA CONTRASENA\t~", 0, true, true, 0, (-sizeY + e));
            Sleep(1000);
            char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
            system(color);
        }
    } while (contrasena != contrasenaConfi || contrasena.length() < 8);
    return 0;
}