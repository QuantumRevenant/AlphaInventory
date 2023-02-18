#ifndef PRODUCTOCONTROLLER_H
#define PRODUCTOCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Producto.cpp"

using namespace std;

class ProductoController
{
private:
    vector<Producto> vectorProducto;

public:
    ProductoController();
    void add(Producto);
    Producto get(int);
    void modify(Producto, int);

    int getNewCodProducto();
    bool nombreRegistrado(string);
    bool codigoRegistrado(int);

    void saveFile();
    void getFile();
};
ProductoController::ProductoController() { getFile(); }

void ProductoController::add(Producto obj) { vectorProducto.push_back(obj); }
Producto ProductoController::get(int pos) { return vectorProducto[pos]; }
void ProductoController::modify(Producto temp, int obj) { vectorProducto[obj] = temp; }

int ProductoController::getNewCodProducto() { return vectorProducto.size(); }
bool ProductoController::nombreRegistrado(string _nombre)
{
    for (Producto x : vectorProducto)
    {
        if (aMayuscula(x.getNombre()) == aMayuscula(_nombre))
            return true;
    }
    return false;
}
bool ProductoController::codigoRegistrado(int _cod)
{
    for (Producto x : vectorProducto)
    {
        if (_cod == x.getCodProducto())
            return true;
    }
    return false;
}
void ProductoController::saveFile()
{
    try
    {
        fstream archivoProductos;
        archivoProductos.open("../data/productos.csv", ios::out);
        if (archivoProductos.is_open())
        {
            for (Producto obj : vectorProducto)
            {
                archivoProductos << obj.getCodProducto() << ","
                                 << obj.getCodMarca() << ","
                                 << obj.getNombre() << ","
                                 << obj.getPrecioUnitario() << ","
                                 << obj.getStock() << ","
                                 << obj.getNumComponentes() << ",";
                for (Componente x : obj.getVectorComponentes())
                    archivoProductos << x.getNombre() << ","
                                     << x.getCantidad() << ",";
                archivoProductos << endl;
            }
            archivoProductos.close();
        }
    }
    catch (exception e)
    {

        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void ProductoController::getFile()
{
    // try
    // {
        int i;
        int j;
        size_t posi;
        string linea;
        fstream archivoProductos;
        vectorProducto.clear();
        archivoProductos.open("../data/productos.csv", ios::in);
        if (archivoProductos.is_open())
        {
            while (!archivoProductos.eof() && getline(archivoProductos, linea))
            {
                vector<string> temporal = {};
                vector<Componente> temporalComponentes = {};
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                for (int i = 6; i < temporal.size(); i += 2)
                {
                    Componente objComponente(temporal[i], temporal[i + 1]);
                    temporalComponentes.push_back(objComponente);
                }
                Producto obj;
                obj.setCodProducto(stoi(temporal[0]));
                obj.setCodMarca(stoi(temporal[1]));
                obj.setNombre(temporal[2]);
                obj.setPrecioUnitario(stod(temporal[3]));
                obj.setStock(stoi(temporal[4]));
                obj.setComponentes(temporalComponentes);
                cout << "Loading Producto " << temporal[2] << " - " << obj.getNombre() << endl;
                add(obj);
            }
            archivoProductos.close();
        }
    // }
    // catch (exception e)
    // {
    //     cout << "Ocurrio un error al leer el archivo";
    // }
}
#endif // PRODUCTOCONTROLLER_H
