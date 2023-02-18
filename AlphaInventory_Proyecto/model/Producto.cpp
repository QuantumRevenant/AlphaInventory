#ifndef PRODUCTO_CPP
#define PRODUCTO_CPP
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "clases.h"
#include "FuncionesGenerales.h"
#include "Componente.cpp"
#include "Marca.cpp"

Producto::Producto() {}
Producto::Producto(int codProducto, int codMarca, string nombre, double precioUnitario, int stock, vector<Componente> vectorComponentes)
{
    this->codProducto = codProducto;
    this->codMarca = codMarca;
    this->nombre = nombre;
    this->precioUnitario = precioUnitario;
    this->stock = stock;
    this->numComponentes = vectorComponentes.size();
    this->vectorComponentes = vectorComponentes;
}
Producto::~Producto() {}

void Producto::setCodProducto(int codProducto) { this->codProducto = codProducto; }
void Producto::setCodMarca(int codMarca) { this->codMarca = codMarca; }
void Producto::setNombre(string nombre) { this->nombre = nombre; }
void Producto::setPrecioUnitario(double precioUnitario) { this->precioUnitario = precioUnitario; }
void Producto::setStock(int stock) { this->stock = stock; }
void Producto::setNumComponentes(int numComponentes) { this->numComponentes = numComponentes; }
void Producto::setComponentes(vector<Componente> vector)
{
    vectorComponentes = vector;
    setNumComponentes(vectorComponentes.size());
}
void Producto::modifyStock(int value = 1) { stock += value; }

int Producto::getCodProducto() { return codProducto; }
int Producto::getCodMarca() { return codMarca; }
string Producto::getNombre() { return nombre; }
double Producto::getPrecioUnitario() { return precioUnitario; }
int Producto::getStock() { return stock; }
int Producto::getNumComponentes() { return numComponentes; }
vector<Componente> Producto::getVectorComponentes() { return vectorComponentes; }

void Producto::addComponente(Componente comp) { vectorComponentes.push_back(comp); }
void Producto::deleteComponente(int pos) { vectorComponentes.erase(vectorComponentes.begin() + pos); }
Componente Producto::getComponente(int pos) { return vectorComponentes[pos]; }

#endif // PRODUCTO_CPP
