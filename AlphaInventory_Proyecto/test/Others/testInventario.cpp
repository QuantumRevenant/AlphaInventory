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
    for (int i = 0; i < productoController.size(); i++)
        productos.push_back(productoController.get(i).getNombre());
    if (productos.size() != 0)
    {
        do
        {
            opt = menu("PRODUCTOS", productos);
            if (opt != 0)
            {
                Producto temp;
                temp = productoController.get(opt - 1);
                vector<string> listado;
                for (int i = 0; i < temp.getNumMarcas(); i++)
                    listado.push_back(temp.getMarca(i).getNombreMarca() + "\t" + to_string(temp.getStock(i)));
                menuListado(listado, 0, aMayuscula(temp.getNombre()), true);
            }
        } while (opt != 0);
    }else
    {
        menuError({"No hay productos registrados, volviendo al menu inventario"});
    }
}
void changeDataInventario()
{
    int opt;
    int optP;
    vector<string> inputs;
    vector<string> options1 = {"Editar Nombre", "Anadir Marca", "Eliminar Marca", "Editar Precios"};
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
            optP = menu("MODIFICAR PRODUCTO", options0);
            if (optP != 0 && optP != -1)
            {
                Producto temp;
                temp = productoController.get(optP - 1);
                do
                {
                    opt = menu(temp.getNombre(), options1);
                    switch (opt)
                    {
                    case 1:
                        do
                        {
                            inputs.clear();
                            cin.ignore();
                            menuDatos({"Nuevo Nombre"}, inputs, 0,0, "_CAMBIAR NOMBRE_");
                            if (!productoController.nombreRegistrado(inputs[0]))
                            {
                                temp.setNombre(inputs[0]);
                            }else
                            {
                                menuError({"El nombre ingresado ya exite"});
                            }
                        } while (productoController.nombreRegistrado(inputs[0]));
                        opt = 1;
                        break;
                    case 2:
                        do
                        {
                            opt = menu("AGREGAR MARCAS", optionsM);
                            if (opt != 0 && opt != -1)
                            {
                                if (!temp.marcaRegistrada(opt - 1))
                                {
                                    inputs.clear();
                                    cin.ignore();
                                    menuDatos({"Precio"}, inputs, 0, 0, marcaController.get(opt - 1).getNombreMarca());
                                    if (opt > 0 && opt <= marcaController.size())
                                    {
                                        temp.addMarca(marcaController.get(opt - 1), stof(inputs[0]));
                                        temp.setNumMarcas(temp.getNumMarcas() + 1);
                                    }
                                } else
                                {
                                    menuError({"Marca ya registrada para este producto"});
                                }
                            }
                        } while (opt != 0);
                        opt = 2;
                        break;
                    case 3:
                        do
                        {
                            vector<string> optionsM1;
                            for (int i = 0; i < temp.getNumMarcas(); i++)
                                optionsM1.push_back(temp.getMarca(i).getNombreMarca() + "\tS/" + to_string(temp.getPrecioUnitario(i)));
                            opt = menu("MARCAS", optionsM1);
                            if (opt != 0)
                            {
                                temp.deleteMarca(opt - 1);
                                temp.setNumMarcas(temp.getNumMarcas() - 1);
                            }
                        } while (opt != 0);
                        opt = 3;
                        break;
                    case 4:
                        do
                        {
                            vector<string> optionsM1;
                            for (int i = 0; i < temp.getNumMarcas(); i++)
                                optionsM1.push_back(temp.getMarca(i).getNombreMarca() + "\tS/" + to_string(temp.getPrecioUnitario(i)));
                            opt = menu("MARCAS", optionsM1);
                            if (opt != 0)
                            {
                                inputs.clear();
                                cin.ignore();
                                menuDatos({"Nuevo Precio"}, inputs, 0, 0, aMayuscula(temp.getMarca(opt - 1).getNombreMarca()));
                                temp.modifyPrecioUnitario(stof(inputs[0]), opt - 1);
                            }
                        } while (opt != 0);
                        opt = 4;
                        break;
                    case 0:
                        productoController.modify(temp, optP - 1);
                        productoController.saveFile();
                        opt = 0;
                        break;
                    default:
                        break;
                    }
                } while (opt != 0);
            }
        } else
        {
            if (options0.size() == 0)
            {
                menuError({"NO HAY PRODUCTOS REGISTRADOS"});
            } else
            {
                menuError({"NO HAY MARCAS REGISTRADAS"});
            }
            optP = 0;
        }
    } while (optP != 0);
}
void doAddProducto()
{
    int opt;
    int i;
    vector<Componente> componentes;
    vector<string> inputs;
    vector<string> optionsM;
    for (int i = 0; i < marcaController.size(); i++)
        optionsM.push_back(marcaController.get(i).getNombreMarca());
    do
    {
        int codigo = productoController.getCorrelativo();
        componentes.clear();
        i = 1;
        inputs.clear();
        cin.ignore();
        menuDatos({"Nombre del Producto"}, inputs, 0, 0, "_PRODUCTO [" + to_string(codigo) + "]_");
        string nombre = inputs[0];
        do
        {
            inputs.clear();
            cin.ignore();
            menuDatos({"Nombre del componente", "Cantidad del componente"}, inputs, 0, 0, "_COMPONENTE [" + to_string(i) + "]_");
            Componente temp(inputs[0], inputs[1]);
            componentes.push_back(temp);
            i++;
        } while (menuConfirmar("Desea agregar un nuevo componente"));
        Producto producto(nombre, componentes, codigo);
        do
        {
            opt = menu("AGREGAR MARCAS", optionsM);
            if (opt != 0 && opt != -1)
            {
                bool MRegistrada = false;
                for (int i = 0; i < producto.getNumMarcas(); i++)
                    if (opt == producto.getMarca(i).getCodigoMarca())
                        MRegistrada = true;
                if (!MRegistrada)
                {
                    inputs.clear();
                    cin.ignore();
                    menuDatos({"Precio S/"}, inputs, 0, 0, aMayuscula(marcaController.get(opt - 1).getNombreMarca()));
                    producto.addMarca(marcaController.get(opt - 1), stof(inputs[0]));
                    producto.setNumMarcas(producto.getNumMarcas() + 1);
                } else
                {
                    menuError({"Marca ya registrada para este producto"});
                }
            }
        } while (opt != 0);
        producto.ordenarComponentes();
        productoController.add(producto);
    } while (menuConfirmar("Desea agregar un nuevo producto"));
    productoController.saveFile();
}
void doAddMarca()
{
    int codigo;
    vector<string> inputs;
    do
    {
        codigo = marcaController.getCorrelativo();
        inputs.clear();
        cin.ignore();
        menuDatos({"Nombre de la marca"}, inputs, 0, 0, "_MARCA [" + to_string(codigo) + "]_");
        Marca marca(codigo, inputs[0]);
        marcaController.add(marca);
    } while (menuConfirmar("Desea agregar una nueva marca"));
    marcaController.saveFile();
}