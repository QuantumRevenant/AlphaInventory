#include <iostream>
#include <string>
#include <vector>
#include "../model/kardex.cpp"
#include "../model/models.h"
#include "../controller/kardexController.h"
#include "../controller/compraController.h"
#include "../controller/ventaController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

/*

*/

kardexController KardexController;
VentaController ventaController;
CompraController compraController;

void doVenta()
{
    vector<string> inputs = {"0"};
    string fecha;
    int cantidad;
    if (menuConfirmar("Desea usar la fecha de hoy para registrar la venta"))
    {
        cin.ignore();
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    }
    else
    {
        cin.ignore();
        do
        {
            cout << KardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!KardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }
    
    inputs.clear();
    menuDatos({"cantidad", "codProducto", "observacion"}, inputs);
    string codVenta = createCode("VT",ventaController.size(),5);
    int cantComprobantes = KardexController.getCantidadComprobante(true);
    string comprobante = createCode("BV",cantComprobantes,0);

    kardex movimiento(fecha, stoi(inputs[0]), stoi(inputs[1]), codVenta, comprobante, true, "~~Venta " + to_string(cantComprobantes), inputs[2]);
    KardexController.add(movimiento);
    KardexController.saveFile();
}

void doCompra()
{
    vector<string> inputs = {"0"};
    string fecha;
    int cantidad;
    if (menuConfirmar("Desea usar la fecha de hoy para registrar la compra"))
    {
        cin.ignore();
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    }
    else
    {
        cin.ignore();
        do
        {
            cout << KardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!KardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }
    
    inputs.clear();
    menuDatos({"cantidad", "codProducto", "Factura","observacion"}, inputs);
    string codCompra = createCode("CP",compraController.size(),5);
    int cantComprobantes = KardexController.getCantidadComprobante(false);
    // string comprobante = createCode("BV",cantComprobantes,0);

    kardex movimiento(fecha, stoi(inputs[0]), stoi(inputs[1]), codCompra, inputs[2], false, "~~Compra " + to_string(cantComprobantes), inputs[3]);
    KardexController.add(movimiento);
    KardexController.saveFile();
}
void doMovimiento()
{

}

int main(int argc, char *argv[])
{
    int opt;
    opt = menu("Menu", {"doVenta", "doCompra", "registrarMovimiento"});
    switch (opt)
    {
    case 1:
        doVenta();
        break;
    case 2:
        doCompra();
        break;
    case 3:
        doMovimiento();
        break;
    default:
        break;
    }

    // string input;
    // do
    // {
    //     cin >> input;
    // } while (!validarFormatoFecha(input));

    // cout << currentDateTime().substr(0, currentDateTime().find(' ')) << endl;
    // cout << currentDateTime() << endl;
    // kardex objKardex(currentDateTime().substr(0, currentDateTime().find(' ')), 5, 0, "VN00000", "EB01-1", true, "VENTA", "VENTA DE PRUEBA");

    // kardex objSalida = objKardex;
    // cout << objSalida.getFechaDeEmision() << endl;
    // cout << objSalida.getCantidad() << endl;
    // cout << objSalida.getCodProducto() << endl;
    // cout << objSalida.getCodProceso() << endl;
    // cout << objSalida.getComprobante() << endl;
    // string salida = objSalida.getIsSalida() ? "True" : "False";
    // cout << salida << endl;
    // cout << objSalida.getMotivo() << endl;
    // cout << objSalida.getObservacion() << endl;

    return 0;
}