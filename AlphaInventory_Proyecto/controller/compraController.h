#ifndef COMPRACONTROLLER_H
#define COMPRACONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Compra.cpp"

using namespace std;

class CompraController
{
private:
    vector<Compra> vectorCompra;

public:
    CompraController();
    void        add(Compra);
    int         getCorrelativo();
    void        modify(Compra, int);
    int         size();
    Compra      get(int);
    void        saveFile();
    void        copyFile();
};

CompraController::CompraController()
{
    copyFile();
}
void    CompraController::add(Compra obj)
{
    vectorCompra.push_back(obj);
}
int     CompraController::getCorrelativo()
{
    if(size() == 0)
	{
		return 1;
	}
	else
	{
		return vectorCompra[size() - 1].getCodCompra() + 1;
	}
}
void    CompraController::modify(Compra temp, int obj)
{
    vectorCompra[obj] = temp;
}
int     CompraController::size()
{
    return vectorCompra.size();
}
Compra  CompraController::get(int pos)
{
    return vectorCompra[pos];
}
void    CompraController::saveFile()
{
    try
    {
        fstream archivoCompras;
        archivoCompras.open("../data/compras.csv", ios::app);
        if (archivoCompras.is_open())
        {
            Compra obj = vectorCompra.back();
                archivoCompras << obj.getCodCompra() << ","
                               << obj.getCodProveedor() << ","
                               << obj.getCodUsuario() << ","
                               << obj.getEstado() << ","
                               << obj.getFecha() << ","
                               << obj.getMonto() << ","
                               << endl;
            archivoCompras.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void    CompraController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoCompras;
        vectorCompra.clear();
        archivoCompras.open("../data/compras.csv", ios::in);
        if (archivoCompras.is_open())
        {
            while (!archivoCompras.eof() && getline(archivoCompras, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Compra obj;
                obj.setCodCompra(stoi(temporal[0]));
                obj.setCodProveedor(stoi(temporal[1]));
                obj.setCodUsuario(stoi(temporal[2]));
                if (temporal[3] == "true")
                {
                    obj.setEstado(true);
                }
                else
                {
                    obj.setEstado(false);
                }
                obj.setFecha(temporal[4]);
                obj.setMonto(stod(temporal[5]));
                add(obj);
            }
            archivoCompras.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
        system("pause");
    }
}

#endif // COMPRACONTROLLER_H
