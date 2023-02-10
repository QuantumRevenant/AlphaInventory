#include <iostream>
#include "../controller/productoController.h"
#include "../controller/marcaController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

ProductoController  productoController;
MarcaController     marcaController;

void listarProductos();
vector<string> listarProducto(Producto);
void listarComponentes(Producto);
void listarMarcas();
void addProductos();
void verProducto();
void menuProducto(int);

int main(int argc, char const *argv[])
{
    vector<string> lista = {"Anadir Productos", "Anadir Stock", "Ver Producto"};
    int opt;
    do
    {
        opt = menu("MENU PRODUCTOS", lista);
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
        case 0:
            cout << "Bye :D" << endl;
            break;
        default:
            break;
        }
    } while (opt != 0);
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
void listarMarcas()
{
    cout << "Marcas Registradas:" << endl;
    if (marcaController.size() > 0)
    {
        for (int i = 0; i < marcaController.size(); i++)
            cout << "[" << i + 1 << "]" << marcaController.get(i).getNombreMarca() << endl;
    } else
    {
        cout << "Aun no hay marcas registradas" << endl;
    }
}
vector<string> listarProducto(Producto temp)
{
    vector<string> text;
    text.push_back("Nombre: " + temp.getNombre());
    text.push_back("Precio unitario: S/" + to_string(temp.getPrecioUnitario()));
    return text;
}
void listarComponentes(Producto temp)
{
    for (int i = 0; i < temp.getNumComponentes(); i++)
        cout << "[" << i + 1 << "]" << temp.getComponente(i).getNombre() << "\t" << temp.getComponente(i).getCantidad() << endl;
}
void addProductos()
{
    string opt;
    do
    {
        string nombre;
        float precio;
        vector<Componente> componentes;
        string nombreComponente;
        string cantidadComponente;
        int i = 0;
        cout << "Nombre y Precio" << endl;
        getValue("Nombre: ", &nombre);
        getValue("Precio: S/", &precio);
        system("cls");
        do
        {
            i++;
            Componente comp;
            cout << "Componente [" << i << "]" << endl;
            getValue("Componente: ", &nombreComponente);
            comp.setNombre(nombreComponente);
            getValue("Cantidad: ", &cantidadComponente);
            comp.setCantidad(cantidadComponente);
            componentes.push_back(comp);
            getValue("¿Desea anadir otro componente?(S/s): ", &opt);
            system("cls");
        } while (aMinuscula(opt) == "s");
        Producto objProducto(nombre, precio, componentes);
        objProducto.ordenarComponentes();
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
    Componente comp;
    string nombreComponente;
    string cantidad;
    temp = productoController.get(obj);
    vector<string> lista;
    do
    {
        lista = listarProducto(temp);
        lista.push_back("Anadir Componente");
        lista.push_back("Eliminar Componente");
        opt = menu("EDITAR PRODUCTO", lista);
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
            getValue("Nombre del componente: ", &nombreComponente);
            comp.setNombre(nombreComponente);
            getValue("Cantidad: ", &cantidad);
            comp.setCantidad(cantidad);
            temp.addComponente(comp);
            temp.ordenarComponentes();
            temp.setNumComponentes(temp.getNumComponentes() + 1);
            break;
        case 4:
            system("cls");
            listarComponentes(temp);
            cout << "Componente a eliminar[1-" << temp.getNumComponentes() << "]: ";
            cin >> optComp;
            temp.deleteComponente(optComp - 1);
            temp.ordenarComponentes();
            temp.setNumComponentes(temp.getNumComponentes() - 1);
            break;
        case 0:
            productoController.modify(temp, obj);
            productoController.saveFile();
            break;
        default:
            break;
        }
    } while (opt != 0);
}