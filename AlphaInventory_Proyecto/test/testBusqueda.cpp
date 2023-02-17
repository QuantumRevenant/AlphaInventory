#include <iostream>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
using namespace std;

string aMinuscula(std::string cadena)
{
    for (int i = 0; i < (int)cadena.length(); i++)
    {
        cadena[i] = std::tolower(cadena[i]);
    }
    return cadena;
}
void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

int main()
{
    char opt;
    vector<string> lista = {"berserk", "grateful", "fill", "bashful", "arrive", "wrist", "smart", "muscle", "muscleA", "muscleB"};
    vector<string> similares;
    vector<string> similares2;
    vector<char> busqueda;
    string busquedaString = "";
    string busquedaLista;
    do
    {
        system("cls");
        cout << "--BUSQUEDA: " << busquedaString;
        gotoxy(0,2);
        for(string x:similares)
            cout << x << endl;
        opt = getch();
        switch (opt)
        {
            case '.': break;
            default:
                busqueda.push_back(opt);
                busquedaString.push_back(opt);
                if (similares.size() == 0)
                    for(int i = 0; i < lista.size(); i++)
                    {
                        busquedaLista = lista[i];
                        if (busqueda.back() == busquedaLista[busqueda.size() - 1])
                            similares.push_back(busquedaLista);
                    }
                else
                    for(int i = 0; i < similares.size(); i++)
                    {
                        busquedaLista = similares[i];
                        if (busqueda.back() == busquedaLista[busqueda.size() - 1])
                            similares2.push_back(busquedaLista);
                        similares = similares2;
                        similares2.clear();
                    }
                break;
        }
    } while( opt != '.');
}
