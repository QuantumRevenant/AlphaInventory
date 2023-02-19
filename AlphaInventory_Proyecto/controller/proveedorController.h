#ifndef PROVEEDORCONTROLLER_H
#define PROVEEDORCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Proveedor.cpp"

class ProveedorController
{
private:
    vector<Proveedor> vectorProveedor;

public:
    ProveedorController();
    int getCorrelativo();
    void add(Proveedor);
    void modify(Proveedor, int);
    int size();
    Proveedor get(int);
    int getPosRUC(long long int);
    void saveFile();
    void copyFile();
};

ProveedorController::ProveedorController()
{
    copyFile();
}
int ProveedorController::getCorrelativo()
{
    if (size() == 0)
    {
        return 1;
    }
    else
    {
        return vectorProveedor[size() - 1].getCodProveedor() + 1;
    }
}
void ProveedorController::add(Proveedor obj)
{
    vectorProveedor.push_back(obj);
}
void ProveedorController::modify(Proveedor temp, int obj)
{
    vectorProveedor[obj] = temp;
}
int ProveedorController::size()
{
    return vectorProveedor.size();
}
Proveedor ProveedorController::get(int pos)
{
    return vectorProveedor[pos];
}
int ProveedorController::getPosRUC(long long int RUC)
{
    for (Proveedor x : vectorProveedor)
    {
        if(x.getDocumento()==RUC)
            return x.getCodProveedor();
    }
    return -1;
}
void ProveedorController::saveFile()
{
    try
    {
        fstream archivoProveedores;
        archivoProveedores.open("../data/proveedor.csv", ios::app);
        if (archivoProveedores.is_open())
        {
            Proveedor obj = vectorProveedor.back();
            archivoProveedores << obj.getCodProveedor() << ","
                               << obj.getNombre() << ","
                               << obj.getTipoDocumento() << ","
                               << obj.getDocumento() << ",";
            archivoProveedores << endl;

            archivoProveedores.close();
        }
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void ProveedorController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoProveedores;
        archivoProveedores.open("../data/proveedor.csv", ios::in);
        if (archivoProveedores.is_open())
        {
            while (!archivoProveedores.eof() && getline(archivoProveedores, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Proveedor obj;
                obj.setCodProveedor(stoi(temporal[0]));
                obj.setNombre(temporal[1]);
                obj.setTipoDocumento(temporal[2]);
                obj.setDocumento(stoll(temporal[3]));
                add(obj);
            }
            archivoProveedores.close();
        }
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
}
#endif // PROVEEDORCONTROLLER_H