#include <iostream>
#include "../controller/productoController.h"
#include "../controller/marcaController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

ProductoController productoController;
MarcaController marcaController;

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
            // menuMain();
            break;
        default:
            marcaController.saveFile();
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
    for (int i = 0; i < productoController.getNewCodProducto(); i++)
        productos.push_back(productoController.get(i).getNombre() + "\t\t" + to_string(productoController.get(i).getStock()));
    if (productos.size() != 0)
    {
        do
        {
            opt = menu("PRODUCTOS", productos);
            if (opt != 0)
            {
                Producto temp;
                temp = productoController.get(opt - 1);
                vector<string> listado{to_string(temp.getCodProducto()), marcaController.get(temp.getCodMarca()).getNombreMarca(),
                                       temp.getNombre(), to_string(temp.getPrecioUnitario()), to_string(temp.getStock())};
                for (Componente x : temp.getVectorComponentes())
                    listado.push_back(x.getNombre() + "\t" + x.getCantidad());
                menuListado(listado, 0, aMayuscula(temp.getNombre()), true);
            }
        } while (opt != 0);
    }
    else
    {
        menuError({"No hay productos registrados, volviendo al menu inventario"});
    }
}
void changeDataInventario()
{
    int opt;
    int codigo;
    vector<string> inputs;
    string temporal;
    bool salida;
    vector<Componente> componentes;
    do
    {
        salida = true;
        do
        {
            menuDatos({"Codigo Producto"}, inputs, 0, 0, "Cambiar Datos Producto -\"Salir\" para Salir");

            if (!esNumero(inputs[0]))
            {
                menuError({"Introduce un valor numérico"});
                inputs[0] = "-1";
            }
            else if (stoi(inputs[0]) < 0 || stoi(inputs[0]) >= productoController.getNewCodProducto())
                menuError({"Codigo Fuera de Rango"});

        } while ((stoi(inputs[0]) < 0 || stoi(inputs[0]) >= productoController.getNewCodProducto()) && aMinuscula(inputs[0]) != "salir");

        if (aMinuscula(inputs[0]) == "salir")
            return;
        if (!menuConfirmar("El producto consultado es " + productoController.get(stoi(inputs[0])).getNombre()))
        {
            if (!menuConfirmar("Desea continuar con el proceso"))
                return;
            else
            {
                salida = false;
                cin.ignore();
            }
        }
    } while (!salida);

    codigo = stoi(inputs[0]);
    Producto prodTemporal = productoController.get(codigo);

    if (productoController.getNewCodProducto() != 0)
    {
        do
        {
            vector<string> options = {"Editar Nombre", "Modificar Marca", "Editar Precios", "Editar Componentes"};
            opt = menu("Selecciona que deseas modificar", options);
            inputs.clear();
            componentes.clear();
            switch (opt)
            {
            case 1:
                menuDatos({"Nuevo nombre de producto"}, inputs);
                temporal = inputs[0];
                if (menuConfirmar("Desea que \"" + temporal + "\" sea el nuevo nombre del producto"))
                    prodTemporal.setNombre(temporal);
                break;
            case 2:
                do
                {
                    menuDatos({"Nuevo código de marca"}, inputs);
                    temporal = inputs[0];
                    if (!esNumero(temporal))
                    {
                        menuError({"Introduce un valor numérico"});
                        temporal = "-1";
                    }
                    else if (stoi(temporal) < 0 || stoi(temporal) >= marcaController.getNewCodMarca())
                        menuError({"Codigo Fuera de Rango"});

                } while (stoi(temporal) < 0 || stoi(temporal) >= marcaController.getNewCodMarca()||temporal=="");

                if (menuConfirmar("Desea que\"" + marcaController.get(stoi(temporal)).getNombreMarca() + "\"sea la nueva marca"))
                    prodTemporal.setCodMarca(stoi(temporal));
                break;
            case 3:
                do
                {
                    menuDatos({"Nuevo precio Unitario"}, inputs);
                    temporal = inputs[0];
                    if (!esNumero(temporal))
                    {
                        menuError({"Introduce un valor numérico"});
                        temporal = "-1";
                    }
                } while (stod(temporal) < 0 || temporal=="");

                if (menuConfirmar("Desea que \"" + temporal + "\" sea el nuevo Precio"))
                    prodTemporal.setPrecioUnitario(stod(temporal));
                break;
            case 4:
                do
                {
                    int i = 0;
                    menuDatos({"Nombre del componente", "Cantidad del componente"}, inputs, 0, 0, "_COMPONENTE [" + to_string(i + 1) + "]_");
                    Componente temp(inputs[0], inputs[1]);
                    componentes.push_back(temp);
                    i++;
                } while (menuConfirmar("Desea agregar un nuevo componente"));

                if (menuConfirmar("Desea modificar los componentes"))
                    prodTemporal.setComponentes(componentes);
                break;
            case 0:
                productoController.modify(prodTemporal, codigo);
                productoController.saveFile();
                break;
            }
        } while (opt != 0);
    }
    else
    {
        menuError({"NO HAY PRODUCTOS REGISTRADOS"});
    }
}

void doAddProducto()
{
    int codMarca;
    int opt;
    int i;
    vector<Componente> componentes;
    vector<string> inputs;
    vector<string> optionsM;
    for (int i = 0; i < marcaController.getNewCodMarca(); i++)
        optionsM.push_back(marcaController.get(i).getNombreMarca());
    do
    {
        int codigo = productoController.getNewCodProducto();
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
        if (marcaController.getNewCodMarca() != 0)
        {
            opt = menu("AGREGAR MARCAS", optionsM);
            if (opt != 0 && opt != -1)
            {
                codMarca = opt - 1;
                cin.ignore();
                do
                {
                    inputs.clear();
                    menuDatos({"Precio S/"}, inputs);
                    if (!esNumero(inputs[0]))
                        menuError({"Introduce un valor numérico"});
                } while (!esNumero(inputs[0]));
                double precio = stod(inputs[0]);
                Producto producto(productoController.getNewCodProducto(), codMarca, nombre, precio, 0, componentes);
                productoController.add(producto);
            }
        }
    } while (menuConfirmar("Desea agregar un nuevo producto"));
    productoController.saveFile();
}
void doAddMarca()
{
    int codigo;
    vector<string> inputs;
    do
    {
        codigo = marcaController.getNewCodMarca();
        inputs.clear();
        cin.ignore();
        menuDatos({"Nombre de la marca"}, inputs, 0, 0, "_MARCA [" + to_string(codigo) + "]_");
        Marca marca(codigo, inputs[0]);
        marcaController.add(marca);
    } while (menuConfirmar("Desea agregar una nueva marca"));
    marcaController.saveFile();
}