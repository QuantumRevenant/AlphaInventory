#ifndef COMPRADCONTROLLER_H
#define COMPRADCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/CompraD.cpp"

using namespace std;

class CompraDController
{
private:
    vector<CompraD> vectorCompraD;

public:
    CompraDController();
    void        add(CompraD);
    void        modify(CompraD, int);
    int         size();
    CompraD     get(int);
    void        saveFile();
    void        copyFile();
};

CompraDController::CompraDController()
{
    copyFile();
}
void    CompraDController::add(CompraD obj)
{
    vectorCompraD.push_back(obj);
}
void    CompraDController::modify(CompraD temp, int obj)
{
    vectorCompraD[obj] = temp;
}
int     CompraDController::size()
{
    return vectorCompraD.size();
}
CompraD  CompraDController::get(int pos)
{
    return vectorCompraD[pos];
}
void    CompraDController::saveFile()
{
    try
    {
        fstream archivoComprasD;
        archivoComprasD.open("../data/comprasD.csv", ios::out);
        if (archivoComprasD.is_open())
        {
            for (CompraD obj:vectorCompraD)
            {
                archivoComprasD << obj.getCodCompra() << ","
                                << obj.getCodProducto() << ","
                                << obj.getCantidad() << ","
                                << obj.getPrecio() << ","
                                << obj.getMonto() << ","
                                << obj.getEstado() << ","
                                << endl;
            }
            archivoComprasD.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void    CompraDController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoComprasD;
        archivoComprasD.open("../data/comprasD.csv", ios::in);
        if (archivoComprasD.is_open())
        {
            while (!archivoComprasD.eof() && getline(archivoComprasD, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                CompraD obj;
                obj.setCodCompra(stoi(temporal[0]));
                obj.setCodProducto(stoi(temporal[1]));
                obj.setCantidad(stoi(temporal[2]));
                obj.setPrecio(stod(temporal[3]));
                obj.setMonto(stod(temporal[4]));
                if (temporal[5] == "true")
                {
                    obj.setEstado(true);
                }
                else
                {
                    obj.setEstado(false);
                }
                add(obj);
            }
            archivoComprasD.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
        system("pause");
    }
}

#endif // COMPRADCONTROLLER_H
