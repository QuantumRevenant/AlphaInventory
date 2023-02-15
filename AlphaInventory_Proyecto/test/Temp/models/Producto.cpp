#ifndef PRODUCTO_CPP
#define PRODUCTO_CPP
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "clases.h"
#include "../model/FuncionesGenerales.h"
#include "Componente.cpp"
#include "Marca.cpp"

Producto::Producto() {}
Producto::Producto(string _nombre, vector<Componente> &_Componentes, int _codigo)
{
    nombre = _nombre;
    vectorComponentes = _Componentes;
    codigo = _codigo;
    numMarcas = 0;
    numComponentes = vectorComponentes.size();
}
Producto::~Producto() {}
void    Producto::setCodigo(int _codigo)
{
    codigo = _codigo;
}
void    Producto::setNombre(string _nombre)
{
    nombre = _nombre;
}
void    Producto::setNumComponentes(int _numComponentes)
{
    numComponentes = _numComponentes;
}
void    Producto::setNumMarcas(int _numMarcas)
{
    numMarcas = _numMarcas;
}
void    Producto::modifyPrecioUnitario(float _precio, int pos)
{
    precioUnitario[pos] = _precio;
}
void    Producto::modifyStock(int _stock, int pos)
{
    stock[pos] = _stock;
}
int  Producto::getCodigo()
{
    return codigo;
}
string  Producto::getNombre()
{
    return nombre;
}
int     Producto::getNumComponentes()
{
    return numComponentes;
}
int     Producto::getNumMarcas()
{
    return numMarcas;
}
bool    Producto::marcaRegistrada(int _cod)
{
    for(Marca x:vectorMarcas)
    {
        if (x.getCodigoMarca() == _cod)
        {
            return true;
        } else
        {
            return false;
        }
    }
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
void    Producto::addMarca(Marca marca, float precio)
{
    vectorMarcas.push_back(marca);
    precioUnitario.push_back(precio);
    stock.push_back(0);
}
void    Producto::deleteComponente(int pos)
{
    vectorComponentes.erase(vectorComponentes.begin() + pos);
}
void    Producto::deleteMarca(int pos)
{
    vectorMarcas.erase(vectorMarcas.begin() + pos);
    precioUnitario.erase(precioUnitario.begin() + pos);
    stock.erase(stock.begin() + pos);
}
Componente Producto::getComponente(int pos)
{
    return vectorComponentes[pos];
}
Marca Producto::getMarca(int pos)
{
    return vectorMarcas[pos];
}
float   Producto::getPrecioUnitario(int pos)
{
    return precioUnitario[pos];
}
int    Producto::getStock(int pos)
{
    return stock[pos];
}

#endif // PRODUCTO_CPP
