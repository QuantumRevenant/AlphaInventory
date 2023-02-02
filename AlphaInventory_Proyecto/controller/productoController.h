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
    void    add(Producto);
    int     binarySearch(int, int, string);
    int     partition(int, int);
    void    quickSort(int, int);
    void    ordenarProductos();
    Producto get(string);
    Producto get(int);
};

ProductoController::ProductoController() {}
void ProductoController::add(Producto obj)
{
    vectorProducto.push_back(obj);
}
int ProductoController::partition(int menor, int mayor)
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
void ProductoController::quickSort(int menor, int mayor)
{
    if (menor < mayor)
    {
        int pivote = partition(menor, mayor);
        quickSort(menor, pivote - 1);
        quickSort(pivote + 1, mayor);
    }
}
void ProductoController::ordenarProductos()
{
    quickSort(0, vectorProducto.size() - 1);
}
int ProductoController::binarySearch(int inicio, int _final, string cod)
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
    pos = binarySearch(0, vectorProducto.size() - 1, codigo);
    if (pos != -1)
        return get(pos);
    else
        return obj;
}
Producto ProductoController::get(int pos)
{
    return vectorProducto[pos];
}
#endif // PRODUCTOCONTROLLER_H
