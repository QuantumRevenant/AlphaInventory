#ifndef VENTACONTROLLER_H
#define VENTACONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Venta.cpp"

using namespace std;

class VentaController
{
private:
    vector<Venta> vectorVenta;

public:
    VentaController();
    void        add(Venta);
    int         getCorrelativo();
    void        modify(Venta, int);
    int         size();
    Venta       get(int);
    void        saveFile();
    void        copyFile();
};

VentaController::VentaController()
{
    copyFile();
}
void    VentaController::add(Venta obj)
{
    vectorVenta.push_back(obj);
}
int     VentaController::getCorrelativo()
{
    if(size() == 0)
	{
		return 1;
	}
	else
	{
		return vectorVenta[size() - 1].getCodVenta() + 1;
	}
}
void    VentaController::modify(Venta temp, int obj)
{
    vectorVenta[obj] = temp;
}
int     VentaController::size()
{
    return vectorVenta.size();
}
Venta  VentaController::get(int pos)
{
    return vectorVenta[pos];
}
void    VentaController::saveFile()
{
    try
    {
        fstream archivoVentas;
        archivoVentas.open("../data/ventas.csv", ios::out);
        if (archivoVentas.is_open())
        {
            for (Venta obj:vectorVenta)
            {
                archivoVentas << obj.getCodVenta() << ","
                              << obj.getCodCliente() << ","
                              << obj.getCodUsuario() << ","
                              << obj.getFecha() << ","
                              << obj.getMonto() << ","
                              << obj.getEstado() << ","
                              << endl;
            }
            archivoVentas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void    VentaController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoVentas;
        archivoVentas.open("../data/ventas.csv", ios::in);
        if (archivoVentas.is_open())
        {
            while (!archivoVentas.eof() && getline(archivoVentas, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Venta obj;
                obj.setCodVenta(stoi(temporal[0]));
                obj.setCodCliente(stoi(temporal[1]));
                obj.setCodUsuario(stoi(temporal[2]));
                obj.setFecha(temporal[3]);
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
            archivoVentas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
        system("pause");
    }
}

#endif // VENTACONTROLLER_H
