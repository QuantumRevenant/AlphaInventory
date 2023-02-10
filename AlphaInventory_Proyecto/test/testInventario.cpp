#include <iostream>
#include "../controller/productoController.h"
#include "../controller/marcaController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

ProductoController  productoController;
MarcaController     marcaController;

void doAddInventario();
void askInventario();
void changeDataInventario();
void doAddProducto();
void doAddMarca();

int main(int argc, char const *argv[])
{
    int opt;
    vector<string> options = {"Registrar Compra", "Consultar Inventario", "Modificar Datos de producto", "Anadir Nuevo Producto", "Anadir Nueva Marca"};
    do
    {
        opt = menu("MENU INVENTARIO", options);
        switch (opt)
        {
        case 1:
            doAddInventario();
            break;
        case 2:
            askInventario();
            break;
        case 3:
            changeDataInventario();
            break;
        case 4:
            doAddProducto();
            break;
        case 5:
            doAddMarca();
            break;
        case 6:
            //menuMain();
            break;
        default:
            cout << "Introduzca una opción valida [1-5]" << endl;
            break;
        }
    } while (opt != 0);
    
    return 0;
}

void doAddInventario()
{

}
void askInventario()
{
    int opt;
    vector<string> productos;
    for (size_t i = 0; i < productoController.size(); i++)
        productos.push_back(productoController.get(i).getNombre());
    if (productos.size() != 0)
    {
        do
        {
            opt = menu("PRODUCTOS", productos);
            if (opt != 0)
            {
                for (int i = 0; i < productoController.get(opt - 1).getNumMarcas(); i++)
                    cout << productoController.get(opt - 1).getMarca(i).getNombreMarca() << "\t" << productoController.get(opt - 1).getStock(i) << endl;
                system("pause");
            }
        } while (opt != 0);
    }else
    {
        cout << "No hay productos registrados" << endl;
        system("pause");
    }
}
void changeDataInventario()
{
    int opt0;
    int opt1;
    int opt3;
    int opt4;
    int opt5;
    do
    {
        vector<string> options0;
        for (int i = 0; i < productoController.size(); i++)
            options0.push_back(productoController.get(i).getNombre());
        vector<string> optionsM;
        for (int i = 0; i < marcaController.size(); i++)
            optionsM.push_back(marcaController.get(i).getNombreMarca());
        if (options0.size() != 0 && optionsM.size() != 0)
        {
            opt0 = menu("MODIFICAR PRODUCTO", options0);
            if (opt0 > 0 && opt0 <= productoController.size())
            {
                Producto temp;
                string nombre;
                float precio;
                temp = productoController.get(opt0 - 1);
                vector<string> options1 = {"Editar Nombre", "Anadir Marca", "Eliminar Marca", "Editar Precios"};
                do
                {
                    opt1 = menu(temp.getNombre(), options1);
                    switch (opt1)
                    {
                    case 1:
                        getValue("Nuevo Nombre: ", &nombre);
                        temp.setNombre(nombre);
                        break;
                    case 2:
                        do
                        {
                            opt3 = menu("MARCAS", optionsM);
                            if (opt3 != 0)
                            {
                                getValue("Precio: S/", &precio);
                                if (opt3 > 0 && opt3 <= marcaController.size())
                                    temp.addMarca(marcaController.get(opt3 - 1), precio);
                            }
                        } while (opt3 != 0);
                        break;
                    case 3:
                        do
                        {
                            vector<string> optionsM1;
                            for (int i = 0; i < temp.getNumMarcas(); i++)
                                optionsM1.push_back(temp.getMarca(i).getNombreMarca() + "\tS/" + to_string(temp.getPrecioUnitario(i)));
                            opt4 = menu("MARCAS", optionsM1);
                            if (opt4 != 0)
                                temp.deleteMarca(opt4 - 1);
                        } while (opt4 != 0);
                        break;
                    case 4:
                        do
                        {
                            vector<string> optionsM1;
                            for (int i = 0; i < temp.getNumMarcas(); i++)
                                optionsM1.push_back(temp.getMarca(i).getNombreMarca() + "\tS/" + to_string(temp.getPrecioUnitario(i)));
                            opt5 = menu("MARCAS", optionsM1);
                            if (opt5 != 0)
                            {
                                getValue("Nuevo Precio: S/", &precio);
                                temp.modifyPrecioUnitario(precio, opt5 - 1);
                            }
                        } while (opt5 != 0);
                        break;
                    case 0:
                        productoController.modify(temp, opt0 - 1);
                        break;
                    default:
                        break;
                    }
                } while (opt1 != 0);
            }
        } else
        {
            system("cls");
            dibujarCuadro();
            if (options0.size() == 0)
            {
                centrarTexto("NO HAY PRODUCTOS REGISTRADOS\n", 0, true, true, 0, -2);
            } else
            {
                centrarTexto("NO HAY MARCAS REGISTRADAS\n", 0, true, true, 0, -2);
            }
            system("pause");
            opt0 = 0;
        }
    } while (opt0 != 0);
}
void doAddProducto()
{
    string opt;
    string opt1;
    int i = 1;
    do
    {
        string nombre;
        vector<Componente> componentes;
        string nombreComp;
        string cantidadComp;
        getValue("Nombre del Producto: ", &nombre);
        do
        {
            getValue("Nombre del componente: ", &nombreComp);
            getValue("Cantidad del componente: ", &cantidadComp);
            Componente temp(nombreComp, cantidadComp);
            componentes.push_back(temp);
            getValue("Desea agregar otro componente?(S/s): ", &opt1);
        } while (aMinuscula(opt1) == "s");
        Producto producto(nombre, componentes);
        producto.ordenarComponentes();
        productoController.add(producto);
        productoController.ordenarProductos();
        getValue("Desea agregar otro producto?(S/s): ", &opt);
    } while (aMinuscula(opt) == "s");
}
void doAddMarca()
{
    string nombre;
    int codigo;
    codigo = marcaController.getCorrelativo();
    getValue("Nombre de la marca: ", &nombre);
    Marca marca(codigo, nombre);
    marcaController.add(marca);
    marcaController.saveFile();
}