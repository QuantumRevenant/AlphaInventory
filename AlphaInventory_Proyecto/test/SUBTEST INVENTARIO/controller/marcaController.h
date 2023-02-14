#ifndef MARCACONTROLLER_H
#define MARCACONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Marca.cpp"

class MarcaController
{
private:
    vector<Marca> vectorMarca;

public:
    MarcaController();

    void add(Marca);
    Marca get(int);
    void modify(Marca, int);

    int getNewCodMarca();
    bool marcaRegistrada(string);

    void saveFile();
    void getFile();
};

MarcaController::MarcaController() { getFile(); }

void MarcaController::add(Marca obj) { vectorMarca.push_back(obj); }
Marca MarcaController::get(int pos) { return vectorMarca[pos]; }
void MarcaController::modify(Marca temp, int obj) { vectorMarca[obj] = temp; }

int MarcaController::getNewCodMarca() { return vectorMarca.size(); }
bool MarcaController::marcaRegistrada(string _nombre)
{
    for (Marca x : vectorMarca)
    {
        if (aMayuscula(x.getNombreMarca()) == aMayuscula(_nombre))
            return true;
        else
            return false;
    }
}

void MarcaController::saveFile()
{
    try
    {
        fstream archivoMarcas;
        archivoMarcas.open("../data/marcas.csv", ios::out);
        if (archivoMarcas.is_open())
        {
            for (Marca obj : vectorMarca)
                archivoMarcas << obj.getCodigoMarca() << "," << obj.getNombreMarca() << ","<<endl;
            archivoMarcas.close();
        }
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void MarcaController::getFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoMarcas;
        archivoMarcas.open("../data/marcas.csv", ios::in);
        if (archivoMarcas.is_open())
        {
            while (!archivoMarcas.eof() && getline(archivoMarcas, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Marca obj(stoi(temporal[0]),temporal[1]);
                add(obj);
            }
            archivoMarcas.close();
        }
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
}
#endif // PRODUCTOCONTROLLER_H