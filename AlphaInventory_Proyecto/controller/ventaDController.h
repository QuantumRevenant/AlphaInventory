#ifndef VENTADCONTROLLER_H
#define VENTADCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/VentaD.cpp"

using namespace std;

class VentaDController
{
private:
    vector<VentaD> vectorVentaD;

public:
    VentaDController();
    void        add(VentaD);
    void        modify(VentaD, int);
    int         size();
    VentaD      get(int);
    void        saveFile();
    void        copyFile();
};

VentaDController::VentaDController()
{
    copyFile();
}
void    VentaDController::add(VentaD obj)
{
    vectorVentaD.push_back(obj);
}
void    VentaDController::modify(VentaD temp, int obj)
{
    vectorVentaD[obj] = temp;
}
int     VentaDController::size()
{
    return vectorVentaD.size();
}
VentaD  VentaDController::get(int pos)
{
    return vectorVentaD[pos];
}
void    VentaDController::saveFile()
{
    try
    {
        fstream archivoVentasD;
        archivoVentasD.open("../data/comprasD.csv", ios::out);
        if (archivoVentasD.is_open())
        {
            for (VentaD obj:vectorVentaD)
            {
                archivoVentasD << obj.getCodVenta() << ","
                               << obj.getCodProducto() << ","
                               << obj.getCantidad() << ","
                               << obj.getPrecio() << ","
                               << obj.getMonto() << ","
                               << endl;
            }
            archivoVentasD.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void    VentaDController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoVentasD;
        archivoVentasD.open("../data/ventasD.csv", ios::in);
        if (archivoVentasD.is_open())
        {
            while (!archivoVentasD.eof() && getline(archivoVentasD, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                VentaD obj;
                obj.setCodVenta(stoi(temporal[0]));
                obj.setCodProducto(stoi(temporal[1]));
                obj.setCantidad(stoi(temporal[2]));
                obj.setPrecio(stod(temporal[3]));
                obj.setMonto(stod(temporal[4]));
                add(obj);
            }
            archivoVentasD.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
        system("pause");
    }
}

#endif // VENTADCONTROLLER_H
