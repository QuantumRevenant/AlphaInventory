#include <iostream>
#include "../model/FuncionesGenerales.h"
#include <vector>
using namespace std;

string menuBusqueda(vector<string> _lista, int separation = 0, string title = "")
{
    char opt;
    int j;
    vector<string> lista = _lista;
    vector<string> similares;
    vector<string> similares2;
    string busqueda = "";
    string busquedaString;
    string busquedaLista;
    do
    {
        int sizeY = 1 + (1 * separation) / 2 - 1;
        int e = 0;
        system("cls");
        dibujarCuadro();
        j = 1;
        if (title != "")
        {
            sizeY += 2 + separation / 2;
            centrarTexto(title, 0, true, true, 0, (-sizeY + e));
            e += 2 + separation;
        }
        centrarTexto(">_" + busqueda, 0, true, true, 0, (-sizeY + e));
        e += 2 + separation;
        if (similares.size() == lista.size())
            similares.clear();
        for (string x:similares)
        {
            centrarTexto("[" + to_string(j) + "] " + x, 0, true, true, 0, (-sizeY + e));
            j++;
            e += 1 + separation;
        }
        gotoxy(150 + busqueda.size(), 13);
        opt = getch();
        switch (opt)
        {
            case '\b':
                if (busqueda.size() != 0)
                {
                    busqueda.erase(busqueda.begin() + busqueda.size() - 1);
                    similares.clear();
                    for(int i = 0; i < lista.size(); i++)
                    {
                        busquedaLista = "";
                        busquedaString = aMinuscula(busqueda);
                        for (int k = 0; k < busqueda.size(); k++)
                        {
                            string h = aMinuscula(lista[i]);
                            busquedaLista.push_back(h[k]);
                        }
                        if (busquedaString == busquedaLista)
                            similares.push_back(lista[i]);
                    }
                }
                break;
            default:
                if (isdigit(opt))
                    break;            
                busqueda.push_back(opt);
                if (similares.size() == 0)
                    for(int i = 0; i < lista.size(); i++)
                    {
                        busquedaLista = "";
                        busquedaString = aMinuscula(busqueda);
                        for (int k = 0; k < busqueda.size(); k++)
                        {
                            string h = aMinuscula(lista[i]);
                            busquedaLista.push_back(h[k]);
                        }
                        if (busquedaString == busquedaLista)
                            similares.push_back(lista[i]);
                    }
                else
                {
                    for(int i = 0; i < similares.size(); i++)
                    {
                        busquedaLista = "";
                        busquedaString = aMinuscula(busqueda);
                        for (int k = 0; k < busqueda.size(); k++)
                        {
                            string h = aMinuscula(similares[i]);
                            busquedaLista.push_back(h[k]);
                        }
                        if (busquedaString == busquedaLista)
                            similares2.push_back(similares[i]);
                    }
                    similares = similares2;
                    similares2.clear();
                }
                break;
        }
    } while(!isdigit(opt));

    return similares[int(opt) - 49];
}

int main()
{
    vector<string> lista = {"berserk", "grateful", "fill", "bashful", "arrive", "wrist", "smart", "muscle", "muscleA", "muscleB"};
    string busqueda = menuBusqueda(lista, 0, "_TEST BUSQUEDA_");
    system("cls");
    cout << busqueda << endl;
    system("pause");
}
