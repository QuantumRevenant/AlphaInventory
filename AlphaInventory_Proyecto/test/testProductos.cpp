#include <iostream>
#include "../controller/productoController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

ProductoController productoController;

void listarProductos();
void addProductos();
void verProducto();

int main(int argc, char const *argv[])
{
    //productoController.copyFile();
    int opt;
    do
    {
        cout << "Menu productos" << endl;
        listarProductos();
        cout << " \nAnadir productos-------------[1]" << endl;
        cout << "Anadir stock-----------------[2]" << endl;
        cout << "Ver Producto-----------------[3]" << endl;
        cout << "Salir------------------------[4]" << endl;
        getValue("Ingrese Opcion[1-4]: ", &opt);
        switch (opt)
        {
        case 1:
            system("cls");
            addProductos();
            break;
        case 2:
            
            break;
        case 3:
            system("cls");
            verProducto();
            break;
        case 4:
            cout << "Bye :D" << endl;
            break;
        default:
            cout << "Ingrese una opcion valida[1-4]" << endl;
            system("pause");
            system("cls");
            break;
        }
    } while (opt !=4);
    

    return 0;
}

void listarProductos()
{
    cout << "\nProductos Registrados:" << endl;
    if (productoController.size() > 0)
    {
        for (int i = 0; i < productoController.size(); i++)
            cout << "[" << i + 1 << "]" << productoController.get(i).getCodigo() << "\t" << productoController.get(i).getNombre() << "\tS/." << productoController.get(i).getPrecioUnitario() << endl;
    } else
    {
        cout << "Aun no hay productos registrados" << endl;
    }
}
void addProductos()
{
    string opt;
    do
    {
        string nombre;
        float precio;
        vector<Compuesto> componentes;
        string nombreComponente;
        float cantidadComponente;
        int i = 0;

        cout << "Nombre y Precio" << endl;
        getValue("Nombre: ", &nombre);
        getValue("Precio: ", &precio);
        system("cls");
        do
        {
            i++;
            Compuesto comp;
            cout << "Componente [" << i << "]" << endl;
            getValue("Componente: ", &nombreComponente);
            comp.compuesto = nombreComponente;
            getValue("Cantidad: ", &cantidadComponente);
            comp.cantidad = cantidadComponente;
            componentes.push_back(comp);
            getValue("¿Desea anadir otro componente?(S/s)", &opt);
            system("cls");
        } while (aMinuscula(opt) == "s");
        Producto objProducto(nombre, precio, componentes);
        objProducto.ordenarCompuestos();
        productoController.add(objProducto);
        productoController.ordenarProductos();
        productoController.saveFile();
        getValue("¿Desea anadir otro producto?(S/s)", &opt);
        system("cls");
    } while (aMinuscula(opt) == "s");
}
void verProducto()
{
    int opt;
    listarProductos();
    cout << "Salir------------------------[" << productoController.size() + 1 << "]" << endl;
    getValue("Ingrese Opcion: ", &opt);
    switch (opt)
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }
}