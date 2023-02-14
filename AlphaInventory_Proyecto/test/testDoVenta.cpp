#include <iostream>
#include "../model/FuncionesGenerales.h"
#include "../controller/ventaController.h"
#include "../controller/ventaDController.h"
#include "../controller/productoController.h"
#include "../controller/clienteController.h"
using namespace std;

VentaController ventaController;
VentaDController ventaDController;
ProductoController productoController;
ClienteController clienteController;

void doVenta();

int main(int argc, char const *argv[])
{
    doVenta();
    return 0;
}

void doVenta()
{
    int opt;
    string busqueda;
    double montoTotal = 0;
    vector<string> inputs;
    vector<VentaD> carrito;
    vector<string> listado;
    do
    {
        int codigoVenta = ventaController.getCorrelativo();
        opt = menu("_Venta_", {"Agregar producto", "Eliminar Producto", "Finalizar Venta"});
        switch (opt)
        {
        case 1:
            do
            {
                Producto productoTemp;
                int unidades;
                double precio;
                double monto;
                inputs.clear();
                cin.ignore();
                menuDatos({"Codigo de Producto"}, inputs, 0, 0, "BUSQUEDA");
                productoTemp = productoController.get(stoi(inputs[0]) - 1);
                do
                {
                    inputs.clear();
                    cin.ignore();
                    menuDatos({"Unidades por adquirir"}, inputs, 0, 0, aMayuscula(productoTemp.getNombre()));
                    unidades = stoi(inputs[0]);
                    if (unidades > productoTemp.getStock())
                        menuError({"Solo hay " + to_string(productoTemp.getStock()) + " unidades en stock"});
                } while (unidades > productoTemp.getStock());
                if (unidades == 0)
                    break;
                precio = productoTemp.getPrecioUnitario();
                VentaD ventaDTemp(codigoVenta, productoTemp.getCodigo(), unidades, precio, true);
                carrito.push_back(ventaDTemp);
                listado.push_back(to_string(productoTemp.getCodigo()) + "|" + productoTemp.getNombre() + "|" + to_string(precio) + "|" + to_string(unidades) + "|" + to_string(ventaDTemp.getMonto()));
            } while (menuConfirmar("Desea agregar otro producto"));
            opt = 1;
            break;
        case 2:
            do
            {
                opt = menu("ELIMINAR PRODUCTO", listado);
                if (opt != 0 && opt != -1)
                {
                    carrito.erase(carrito.begin() + opt - 1);
                    listado.erase(listado.begin() + opt - 1);
                }
            } while (opt != 0);
            opt = 2;
            break;
        case 3:
            for(VentaD x:carrito)
                montoTotal += x.getMonto();
            listado.push_back("TOTAL S/" + to_string(montoTotal));
            menuListado(listado, 0, "_VENTA_", true);
            if (menuConfirmar("Registrar venta"))
            {
                inputs.clear();
                cin.ignore();
                menuDatos({"Nombre de Cliente", "DNI"}, inputs, 0, 0, "_DATOS DEL CLIENTE_");
                int codCliente = clienteController.getCorrelativo();
                Cliente clienteTemp(codCliente, inputs[0], inputs[1]);
                clienteController.add(clienteTemp);
                for(VentaD x:carrito)
                    ventaDController.add(x);
                int codUsuario = 69;
                Venta venta(codigoVenta, codCliente, codUsuario, montoTotal, true);
                ventaController.add(venta);
            }else
            {
                montoTotal = 0;
                listado.erase(listado.begin() + listado.size() - 1);
            }
            break;
        case 0:
            if (!menuConfirmar("Seguro que desea cancelar la venta"))
                opt = -1;
            break;
        default:
            break;
        }
    } while (opt != 0);
}
