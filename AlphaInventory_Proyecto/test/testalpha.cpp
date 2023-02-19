#include <iostream>
#include <Windows.h>
#include <locale.h>

using namespace std;

int main()
{

    // // Para Linux - Usa locale.h
    // setlocale(LC_ALL, "Spanish");

    // Para Windows - Usa Windows.h
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);


    printf("á ó Ü ¿");
    system("pause");
    return 0;
}