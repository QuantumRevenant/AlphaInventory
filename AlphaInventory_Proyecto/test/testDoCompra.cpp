#include <iostream>
#include "../model/FuncionesGenerales.h"
#include "../controller/compraController.h"
#include "../controller/compraDController.h"
#include "../controller/productoController.h"
#include "../controller/proveedorController.h"
#include "../model/models.h"
using namespace std;

CompraController compraController;
CompraDController compraDController;
ProductoController productoController;
ProveedorController proveedorController;

void doCompra();

int main(int argc, char const *argv[])
{
    doCompra();
    return 0;
}

void doCompra()
{
    int opt;
    double montoTotal = 0;
    vector<string> inputs;
    vector<CompraD> carrito;
    vector<string> listado;
    do
    {
        int codigoCompra = compraController.getCorrelativo();
        opt = menu("_Compra_", {"Agregar producto", "Eliminar Producto", "Finalizar Compra"});
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
                if (productoController.codigoRegistrado(stoi(inputs[0])))
                {
                    productoTemp = productoController.get(stoi(inputs[0]));
                    inputs.clear();
                    menuDatos({"Unidades por adquirir"}, inputs, 0, 0, aMayuscula(productoTemp.getNombre()));
                    unidades = stoi(inputs[0]);
                    if (unidades != 0)
                    {
                        precio = productoTemp.getPrecioUnitario();
                        CompraD compraDTemp(codigoCompra, productoTemp.getCodProducto(), unidades, precio);
                        carrito.push_back(compraDTemp);
                        listado.push_back(to_string(productoTemp.getCodProducto()) + "|" + productoTemp.getNombre() + "|" + to_string(precio) + "|" + to_string(unidades) + "|" + to_string(compraDTemp.getMonto()));
                    }
                }else
                {
                    menuError({"Producto no encontrado"});
                }
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
            for(CompraD x:carrito)
                montoTotal += x.getMonto();
            listado.push_back("TOTAL S/" + to_string(montoTotal));
            menuListado(listado, 0, "_VENTA_", true);
            if (menuConfirmar("Registrar compra"))
            {
                do
                {
                    inputs.clear();
                    cin.ignore();
                    menuDatos({"Nombre de Proveedor", "RUC"}, inputs, 0, 0, "_DATOS DEL PROVEEDOR_");
                    if (inputs[1].size() != 11)
                        menuError({"El RUC debe contener 11 caracteres"});
                } while (inputs[1].size() != 11);
                int codProveedor = proveedorController.getCorrelativo();
                Proveedor proveedorTemp(codProveedor, inputs[0], inputs[1]);
                proveedorController.add(proveedorTemp);
                for(CompraD x:carrito)
                {
                    compraDController.add(x);
                    Producto productoTemp;
                    productoTemp = productoController.get(x.getCodProducto());
                    productoTemp.modifyStock(productoTemp.getStock() + x.getCantidad());
                    productoController.modify(productoTemp, x.getCodProducto());
                }
                int codUsuario = 0;
                Compra compra(codigoCompra, codProveedor, codUsuario, montoTotal, true);
                compraController.add(compra);
                proveedorController.saveFile();
                compraController.saveFile();
                compraDController.saveFile();
                productoController.saveFile();
            }else
            {
                montoTotal = 0;
                listado.erase(listado.begin() + listado.size() - 1);
            }
            break;
        case 0:
            if (!menuConfirmar("Seguro que desea cancelar la compra"))
                opt = -1;
            break;
        default:
            break;
        }
    } while (opt != 0);
}
