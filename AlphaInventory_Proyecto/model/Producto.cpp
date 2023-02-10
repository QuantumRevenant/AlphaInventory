#ifndef PRODUCTO_CPP
#define PRODUCTO_CPP
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "clases.h"
#include "../model/FuncionesGenerales.h"

Producto::Producto() {}
Producto::Producto(string _nombre, float _precio, vector<Componente> &_Componentes)
{
    nombre = _nombre;
    precioUnitario = _precio;
    vectorComponentes = _Componentes;
    codigo = getCodigo();
    numComponentes = vectorComponentes.size();
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
void    Producto::setNumComponentes(int _numComponentes)
{
    numComponentes = _numComponentes;
}
string  Producto::getCodigo()
{
    string cod;
    cod = nombre[0] + to_string(numComponentes);
    for (int i = 0; i < 5 - vectorComponentes.size(); i++)
        cod += "0";
    for(Componente x:vectorComponentes)
    {
        cod += x.getNombre()[0];
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
int     Producto::getNumComponentes()
{
    return numComponentes;
}
int     Producto::partition(int menor, int mayor)
{
    Componente pivote = vectorComponentes[mayor];
    int i = menor - 1;
    for (int j = menor; j <= mayor - 1; j++)
        if (vectorComponentes[j].getNombre() < pivote.getNombre())
        {
            i++;
            swap(vectorComponentes[i], vectorComponentes[j]);
        }
    swap(vectorComponentes[i + 1], vectorComponentes[mayor]);
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
void    Producto::ordenarComponentes()
{
    quickSort(0, vectorComponentes.size() - 1);
}
void    Producto::addComponente(Componente comp)
{
    vectorComponentes.push_back(comp);
}
void    Producto::deleteComponente(int pos)
{
    vectorComponentes.erase(vectorComponentes.begin() + pos);
}
Componente Producto::getComponente(int pos)
{
    return vectorComponentes[pos];
}

#endif // PRODUCTO_CPP
