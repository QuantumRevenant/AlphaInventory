#include <iostream>
#include "../controller/programController.h"
#include "../controller/cajaController.h"
#include "../model/FuncionesGenerales.h"
#include "../controller/ventaController.h"
#include "../controller/ventaDController.h"
#include "../controller/clienteController.h"
#include "../controller/productoController.h"
#include "../controller/usuarioController.h"
#include "../controller/controllers.h"
#include "../model/models.h"
using namespace std;

VentaController ventaController;
VentaDController ventaDController;
ClienteController clienteController;
ProductoController productoController;
usuarioController UsuarioController;
programController progController;
CajaController cajaController;

void menuRecords();
void askEstadoCaja();
void doConsultarRegistro(int);
void doBuscarRegistro();

int main(int argc, char const *argv[])
{
    menuRecords();
    return 0;
}

void menuRecords()
{
    int opt;
    do
    {
        vector<string> options = {"Estado de Caja", "Registros Personales", "Buscar Registros"}; // Carritos de compra, etc
        opt = menu("_MENU REGISTROS_", options);

        switch (opt)
        {
        case 1:
            askEstadoCaja();
            break;
        case 2:
            doConsultarRegistro(progController.getSesionKey());
            break;
        case 3:
            doBuscarRegistro();
            break;
        case 0:
            //menuMain();
            break;
        }
    } while (opt != 0);
    
}

void askEstadoCaja()
{
    menuListado({"S/" + to_string(cajaController.getSaldo())}, 0, "_SALDO ACTUAL_", true);
}
void doConsultarRegistro(int cod)
{
    int opt;
    int codUsuario = cod;
    vector<Venta> registro;
    vector<string> listaRegistro;
    for (int i = 0; i < ventaController.size(); i++)
    {
        Venta vTemp = ventaController.get(i);
        if (vTemp.getCodUsuario() == codUsuario)
            registro.push_back(vTemp);
    }
    if (registro.size() == 0)
    {
        menuError({"Aun no se hicieron ventas"});
    } else
    {
        for(Venta x:registro)
            listaRegistro.push_back(to_string(x.getCodVenta()) + "\tS/" + to_string(x.getMonto()));
        do
        {
            vector<string> listaVenta;
            opt = menu("_REGISTRO DE VENTAS_", listaRegistro);
            switch (opt)
            {
            case -1:
                break;
            case 0:
                break;
            default:
                Venta vTemp;
                Cliente cTemp;
                vector<VentaD> registroVentaD;
                vTemp = ventaController.get(opt - 1);
                cTemp = clienteController.get(vTemp.getCodCliente() - 1);
                listaVenta.push_back("Nombre del Cliente: " + cTemp.getNombre());
                listaVenta.push_back("DNI del Cliente: " + cTemp.getDocumento());
                listaVenta.push_back("Productos:");
                for (int i = 0; i < ventaDController.size(); i++)
                {
                    VentaD vDTemp = ventaDController.get(i);
                    if (vDTemp.getCodVenta() == opt)
                    {
                        Producto pTemp;
                        pTemp = productoController.get(vDTemp.getCodProducto() - 1);
                        listaVenta.push_back("\t" + pTemp.getNombre() + "\tS/" + to_string(vDTemp.getPrecio()) + "\t" + to_string(vDTemp.getCantidad()) + "u\tS/" + to_string(vDTemp.getMonto()));
                    }
                }
                listaVenta.push_back("Monto total: S/" + to_string(vTemp.getMonto()));
                menuListado(listaVenta);
                break;
            }
        } while (opt != 0);
    }
}
void doBuscarRegistro()
{
    int opt;
    vector<string> usuarios;
    for (int i = 0; i < UsuarioController.size(); i++)
    {
        Usuario uTemp = UsuarioController.get(i);
        usuarios.push_back(uTemp.getUsername() + "\t" + uTemp.getNombre() + " " + uTemp.getApellidos());
    }
    do
    {
        opt = menu("_USUARIOS_", usuarios);
        switch (opt)
        {
        case -1:
            break;
        case 0:
            break;
        default:
            doConsultarRegistro(opt - 1);
            break;
        }
    } while (opt != 0);
}