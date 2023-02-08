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
    void        add(Marca);
    void        modify(Marca, int);
    int         size();
    int         binarySearch(int, int, int);
    int         partition(int, int);
    void        quickSort(int, int);
    void        ordenarMarcas();
    Marca       get(int);
    Marca       get(int);
    void        saveFile();
    void        copyFile();
};

MarcaController::MarcaController()
{
    copyFile();
}
void    MarcaController::add(Marca obj)
{
    vectorMarca.push_back(obj);
}
void    MarcaController::modify(Marca temp, int obj)
{
    vectorMarca[obj] = temp;
}
int     MarcaController::size()
{
    return vectorMarca.size();
}
int     MarcaController::partition(int menor, int mayor)
{
    Marca pivote = vectorMarca[mayor];
    int i = menor - 1;
    for (int j = menor; j <= mayor - 1; j++)
        if (vectorMarca[j].getCodigoMarca() < pivote.getCodigoMarca())
        {
            i++;
            swap(vectorMarca[i], vectorMarca[j]);
        }
    swap(vectorMarca[i + 1], vectorMarca[mayor]);
    return i + 1;
}
void    MarcaController::quickSort(int menor, int mayor)
{
    if (menor < mayor)
    {
        int pivote = partition(menor, mayor);
        quickSort(menor, pivote - 1);
        quickSort(pivote + 1, mayor);
    }
}
void    MarcaController::ordenarMarcas()
{
    quickSort(0, size() - 1);
}
int     MarcaController::binarySearch(int inicio, int _final, int cod)
{
    if (_final >= inicio)
    {
        int mitad = inicio + (_final - inicio) / 2;
        if (vectorMarca[mitad].getCodigoMarca() == cod)
            return mitad;
        if (vectorMarca[mitad].getCodigoMarca() > cod)
            return binarySearch(inicio, mitad - 1, cod);
        return binarySearch(mitad + 1, _final, cod);
    }
    return -1;
}
Marca MarcaController::get(int codigo)
{
    Marca obj;
    int pos;
    obj.setNombreMarca("error");
    pos = binarySearch(0, size() - 1, codigo);
    if (pos != -1)
        return get(pos);
    else
        return obj;
}
Marca MarcaController::get(int pos)
{
    return vectorMarca[pos];
}
void    MarcaController::saveFile()
{
    try
    {
        fstream archivoMarcas;
        archivoMarcas.open("../data/marcas.csv", ios::out);
        if (archivoMarcas.is_open())
        {
            for (Marca obj:vectorMarca)
            {
                archivoMarcas << obj.getCodigoMarca() << "," << obj.getNombreMarca() << ",";
                archivoMarcas << endl;
            }
            archivoMarcas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
    
}
void    MarcaController::copyFile()
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
                while ((posi = linea.find(";")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Marca obj;
                obj.setCodigoMarca(stoi(temporal[0]));
                obj.setNombreMarca(temporal[1]);
                add(obj);
            }
            archivoMarcas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
    
}
#endif // PRODUCTOCONTROLLER_H