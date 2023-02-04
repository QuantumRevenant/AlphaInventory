#include <iostream>
#include "../controller/productoController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

ProductoController productoController;

void listarProductos();
void listarProducto(Producto);
void listarComponentes(Producto);
void addProductos();
void verProducto();
void menuProducto(int);

int main(int argc, char const *argv[])
{
    int opt;
    do
    {
        system("cls");
        cout << "Menu productos\n" << endl;
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
            break;
        }
    } while (opt !=4);
    return 0;
}

void listarProductos()
{
    cout << "Productos Registrados:" << endl;
    if (productoController.size() > 0)
    {
        for (int i = 0; i < productoController.size(); i++)
            cout << "[" << i + 1 << "]" << productoController.get(i).getCodigo() << "\t" << productoController.get(i).getNombre() << "\tS/." << productoController.get(i).getPrecioUnitario() << endl;
    } else
    {
        cout << "Aun no hay productos registrados" << endl;
    }
}
void listarProducto(Producto temp)
{
    cout << "Codigo: " << temp.getCodigo() << endl;
    cout << "Nombre: " << temp.getNombre() << endl;
    cout << "Precio unitario: S/" << temp.getPrecioUnitario() << endl;
    cout << "# de componentes: " << temp.getNumCompuestos() << endl;
    cout << "Componentes:" << endl;
    listarComponentes(temp);
}
void listarComponentes(Producto temp)
{
    for (int i = 0; i < temp.getNumCompuestos(); i++)
        cout << "[" << i + 1 << "]" << temp.getCompuesto(i).compuesto << "\t" << temp.getCompuesto(i).cantidad << endl;
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
            getValue("¿Desea anadir otro componente?(S/s): ", &opt);
            system("cls");
        } while (aMinuscula(opt) == "s");
        Producto objProducto(nombre, precio, componentes);
        objProducto.ordenarCompuestos();
        productoController.add(objProducto);
        productoController.ordenarProductos();
        productoController.saveFile();
        getValue("¿Desea anadir otro producto?(S/s): ", &opt);
        system("cls");
    } while (aMinuscula(opt) == "s");
}
void verProducto()
{
    int opt;
    int limit = productoController.size() + 1;
    do
    {
        system("cls");
        listarProductos();
        cout << "\n[" << limit << "] Salir" << endl;
        getValue("Ingrese Opcion: ", &opt);
        if (opt > 0 && opt < limit)
        {
            menuProducto(opt - 1);
        } else if (opt == limit)
        {
            break;
        }else
        {
            cout << "Ingrese una opcion valida[1-" << limit << "]" << endl;
            system("pause");
        }
    } while (opt != 3);
}
void menuProducto(int obj)
{
    int opt;
    int optComp;
    Producto temp;
    string nombre;
    float precio;
    Compuesto comp;
    string nombreCompuesto;
    float cantidad;
    temp = productoController.get(obj);
    do
    {
        system("cls");
        listarProducto(temp);
        cout << "\n";
        cout << "Opciones:\n";
        cout << "[1] Editar Nombre\n";
        cout << "[2] Editar Precio\n";
        cout << "[3] Anadir Componente\n";
        cout << "[4] Eliminar Componente\n";
        cout << "[5] Salir\n";
        getValue("Ingrese opcion[1-5]:", &opt);
        switch (opt)
        {
        case 1:
            system("cls");
            cout << "Nombre: " << temp.getNombre() << endl;
            getValue("Nuevo Nombre: ", &nombre);
            temp.setNombre(nombre);
            break;
        case 2:
            system("cls");
            cout << "Precio Unitario: S/" << temp.getPrecioUnitario() << endl;
            getValue("Nuevo Precio Unitario: S/", &precio);
            temp.setPrecioUnitario(precio);
            break;
        case 3:
            system("cls");
            getValue("Nombre del componente: ", &nombreCompuesto);
            comp.compuesto = nombreCompuesto;
            getValue("Cantidad: ", &cantidad);
            comp.cantidad = cantidad;
            temp.addCompuesto(comp);
            temp.ordenarCompuestos();
            temp.setNumCompuestos(temp.getNumCompuestos() + 1);
            break;
        case 4:
            system("cls");
            listarComponentes(temp);
            cout << "Componente a eliminar[1-" << temp.getNumCompuestos() << "]: ";
            cin >> optComp;
            temp.deleteCompuesto(optComp - 1);
            temp.ordenarCompuestos();
            temp.setNumCompuestos(temp.getNumCompuestos() - 1);
            break;
        case 5:
            productoController.modify(temp, obj);
            productoController.saveFile();
            break;
        default:
            cout << "Ingrese una opcion valida[1-5]\n";
            system("pause");
            break;
        }
    } while (opt != 5);
}