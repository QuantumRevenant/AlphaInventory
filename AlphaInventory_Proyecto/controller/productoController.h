#ifndef PRODUCTOCONTROLLER_H
#define PRODUCTOCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Producto.cpp"

class ProductoController
{
private:
    vector<Producto> vectorProducto;

public:
    ProductoController();
    void        add(Producto);
    int         size();
    int         binarySearch(int, int, string);
    int         partition(int, int);
    void        quickSort(int, int);
    void        ordenarProductos();
    Producto    get(string);
    Producto    get(int);
    void        saveOnFile(Producto);
    void        saveFile();
    void        copyFile();
};

ProductoController::ProductoController() {}
void    ProductoController::add(Producto obj)
{
    vectorProducto.push_back(obj);
}
int     ProductoController::size()
{
    return vectorProducto.size();
}
int     ProductoController::partition(int menor, int mayor)
{
    Producto pivote = vectorProducto[mayor];
    int i = menor - 1;
    for (int j = menor; j <= mayor - 1; j++)
        if (vectorProducto[j].getCodigo() < pivote.getCodigo())
        {
            i++;
            swap(vectorProducto[i], vectorProducto[j]);
        }
    swap(vectorProducto[i + 1], vectorProducto[mayor]);
    return i + 1;
}
void    ProductoController::quickSort(int menor, int mayor)
{
    if (menor < mayor)
    {
        int pivote = partition(menor, mayor);
        quickSort(menor, pivote - 1);
        quickSort(pivote + 1, mayor);
    }
}
void    ProductoController::ordenarProductos()
{
    quickSort(0, size() - 1);
}
int     ProductoController::binarySearch(int inicio, int _final, string cod)
{
    if (_final >= inicio)
    {
        int mitad = inicio + (_final - inicio) / 2;
        if (vectorProducto[mitad].getCodigo() == cod)
            return mitad;
        if (vectorProducto[mitad].getCodigo() > cod)
            return binarySearch(inicio, mitad - 1, cod);
        return binarySearch(mitad + 1, _final, cod);
    }
    return -1;
}
Producto ProductoController::get(string codigo)
{
    Producto obj;
    int pos;
    obj.setNombre("error");
    pos = binarySearch(0, size() - 1, codigo);
    if (pos != -1)
        return get(pos);
    else
        return obj;
}
Producto ProductoController::get(int pos)
{
    return vectorProducto[pos];
}
void    ProductoController::saveFile()
{
    try
    {
        fstream archivoProductos;
        archivoProductos.open("../data/productos.csv", ios::out);
        if (archivoProductos.is_open())
        {
            for (Producto obj:vectorProducto)
            {
                archivoProductos << obj.getCodigo() << ";" << obj.getNombre() << ";" << obj.getPrecioUnitario() << ";" << obj.getNumCompuestos() << ";";
                for (int i = 0; i < obj.getNumCompuestos(); i++)
                    archivoProductos << obj.getCompuesto(i).compuesto << ";" << obj.getCompuesto(i).cantidad << ";";
                archivoProductos << endl;
            }
            archivoProductos.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
    
}
void    ProductoController::copyFile()
{
    try
    {
        int i;
        int j;
        size_t posi;
        string linea;
        vector<string> temporal;
        fstream archivoProductos;
        archivoProductos.open("../data/productos.csv", ios::in);
        if (archivoProductos.is_open())
        {
            while (!archivoProductos.eof() && getline(archivoProductos, linea))
            {
                i = 0;
                while ((posi = linea.find(";")) != string::npos)
                {
                    temporal[i] = linea.substr(0, posi);
                    linea.erase(0, posi + 1);
                    i++;
                }
                Producto obj;
                obj.setCodigo(temporal[0]);
                obj.setNombre(temporal[1]);
                obj.setPrecioUnitario(stof(temporal[2]));
                obj.setNumCompuestos(stoi(temporal[3]));
                j = 4;
                for (int i = 0; i < obj.getNumCompuestos(); i++)
                {
                    Compuesto comp;
                    comp.compuesto = temporal[j];
                    comp.cantidad = stof(temporal[j + 1]);
                    obj.addCompuesto(comp);
                    j = j + 2;
                }
                add(obj);
            }
            archivoProductos.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
    
}
#endif // PRODUCTOCONTROLLER_H
