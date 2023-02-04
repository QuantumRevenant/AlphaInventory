#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Clases.h"
#include "../model/FuncionesGenerales.h"

Producto::Producto() {}
Producto::Producto(string _nombre, float _precio, vector<Compuesto> &_compuestos)
{
    nombre = _nombre;
    precioUnitario = _precio;
    vectorCompuestos = _compuestos;
    codigo = getCodigo();
    numCompuestos = vectorCompuestos.size();
}
Producto::~Producto() {}
void    Producto::setCodigo(string _codigo)
{
    codigo = _codigo;
}
void    Producto::setNombre(string _nombre)
{
    nombre = _nombre;
}
void    Producto::setPrecioUnitario(float _precioUnitario)
{
    precioUnitario = _precioUnitario;
}
void    Producto::setNumCompuestos(int _numCompuestos)
{
    numCompuestos = _numCompuestos;
}
string  Producto::getCodigo()
{
    string cod;
    cod = nombre[0] + to_string(numCompuestos);
    for (int i = 0; i < 5 - vectorCompuestos.size(); i++)
        cod += "0";
    for(Compuesto x:vectorCompuestos)
    {
        cod += x.compuesto[0];
        if (cod.size() == 7)
            break;        
    }
    return cod;
}
string  Producto::getNombre()
{
    return nombre;
}
float   Producto::getPrecioUnitario()
{
    return precioUnitario;
}
int     Producto::getNumCompuestos()
{
    return numCompuestos;
}
int     Producto::partition(int menor, int mayor)
{
    Compuesto pivote = vectorCompuestos[mayor];
    int i = menor - 1;
    for (int j = menor; j <= mayor - 1; j++)
        if (vectorCompuestos[j].compuesto < pivote.compuesto)
        {
            i++;
            swap(vectorCompuestos[i], vectorCompuestos[j]);
        }
    swap(vectorCompuestos[i + 1], vectorCompuestos[mayor]);
    return i + 1;
}
void    Producto::quickSort(int menor, int mayor)
{
    if (menor < mayor)
    {
        int pivote = partition(menor, mayor);
        quickSort(menor, pivote - 1);
        quickSort(pivote + 1, mayor);
    }
}
void    Producto::ordenarCompuestos()
{
    quickSort(0, vectorCompuestos.size() - 1);
}
void    Producto::addCompuesto(Compuesto comp)
{
    vectorCompuestos.push_back(comp);
}
void    Producto::deleteCompuesto(int pos)
{
    vectorCompuestos.erase(vectorCompuestos.begin() + pos);
}
Compuesto Producto::getCompuesto(int pos)
{
    return vectorCompuestos[pos];
}

#endif // PRODUCTO_H
