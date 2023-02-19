#include <iostream>
#include <string>
#include <vector>
#include "../model/kardex.cpp"
#include "../model/models.h"
#include "../controller/KardexController.h"
#include "../controller/compraController.h"
#include "../controller/ventaController.h"
#include "../controller/productoController.h"
#include "../model/CompraD.cpp"
#include "../model/FuncionesGenerales.h"
using namespace std;

/*

*/

KardexController kardexController;
VentaController ventaController;
CompraController compraController;
ProductoController productoController;

// void doVenta()
// {
// vector<string> inputs = {"0"};
// string fecha;
// int cantidad;
// if (menuConfirmar("Desea usar la fecha de hoy para registrar la venta"))
// {
//     cin.ignore();
//     fecha = currentDateTime().substr(0, currentDateTime().find(' '));
// }
// else
// {
//     cin.ignore();
//     do
//     {
//         cout << kardexController.validarFormatoFecha(inputs[0]);
//         system("pause");
//         inputs.clear();
//         menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
//     } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
//     if (aMinuscula(inputs[0]) == "salir")
//         return;
//     fecha = inputs[0];
// }

// inputs.clear();
// menuDatos({"cantidad", "codProducto", "observacion"}, inputs);
// string codVenta = createCode("VT",ventaController.size(),5);
// int cantComprobantes = kardexController.getCantidadComprobante(true);
// string comprobante = createCode("BV",cantComprobantes,0);

// kardex movimiento(fecha, stoi(inputs[0]), stoi(inputs[1]), codVenta, comprobante, true, "~~Venta " + to_string(cantComprobantes), inputs[2]);
// kardexController.add(movimiento);
// kardexController.saveFile();
// }

void doCompra()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;

    long long int proveedorRUC;
    int codProducto;
    int cantProducto;
    double montoProducto;
    string comprobante;
    string fecha;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(false);

    vector<CompraD> carrito;
    vector<kardex> kardexCarrito;
    CompraD tempCompraD;
    kardex tempKardex;

    menuListado({"Inicializando Compra..."}, 0, "Compra #" + to_string(compraController.size() + 1), false);
    Sleep(1000);

    cout << "here" << endl;
    // FECHA
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
            cout << kardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }

    inputs.clear();
    // RUC
    do
    {
        inputs.clear();
        menuDatos({"RUC"}, inputs, 0, 0, "Datos del Proveedor Compra #" + to_string(compraController.size() + 1)); // Proveedores
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (inputs[0].size() != 11)
            menuError({"El RUC tiene 11 Dígitos"});
    } while (!esNumero(inputs[0]) || inputs[0].size() != 11 || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    proveedorRUC = stoll(inputs[0]);
    inputs.clear();
    // COMPROBANTE COMPRA PRODUCTO
    do
    {
        cin.ignore();
        inputs.clear();
        menuDatos({"Comprobante de Compra"}, inputs, 0, 0, "Datos del Comprobante Compra #" + to_string(compraController.size() + 1)); // Producto
        if (aMinuscula(inputs[0]) == "salir")
            return;
    } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));

    comprobante = inputs[0];
    inputs.clear();

    do
    {
        opt = menu("_Carrito de Compra_ #" + to_string(compraController.size() + 1), {"Agregar producto", "Eliminar Producto", "Mirar Carrito de Compra", "Finalizar Compra"});
        switch (opt)
        {
        case 1:
            // CODIGO PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Producto"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (stoi(inputs[0]) >= productoController.getNewCodProducto())
                    menuError({"Producto no registrado"});
            } while (!esNumero(inputs[0]) || stoi(inputs[0]) >= productoController.getNewCodProducto() || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                break;

            codProducto = stoi(inputs[0]);
            inputs.clear();

            // CANTIDAD PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            cantProducto = stoi(inputs[0]);
            inputs.clear();

            // PRECIO COMPRA PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Costo Unitario"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            montoProducto = stoi(inputs[0]);
            inputs.clear();

            tempCompraD.setCodCompra(compraController.size());
            tempCompraD.setCodProducto(codProducto);
            tempCompraD.setCantidad(cantProducto);
            tempCompraD.setPrecio(montoProducto);
            carrito.push_back(tempCompraD);
            break;
        case 2:
            do
            {
                listado.clear();
                for (CompraD x : carrito)
                    listado.push_back(productoController.get(x.getCodProducto()).getNombre());
                opt = menu("Suprimir Productos Compra #" + to_string(compraController.size() + 1), listado);
                if (opt != 0 && opt != -1)
                {
                    carrito.erase(carrito.begin() + opt - 1);
                    listado.erase(listado.begin() + opt - 1);
                }
            } while (opt != 0);
            opt = 2;
            break;

        case 3:
            listado.clear();
            for (CompraD x : carrito)
                listado.push_back(productoController.get(x.getCodProducto()).getNombre());
            menuListado(listado, 0, "Compra #" + to_string(compraController.size() + 1));
            break;

        case 4:
            listado.clear();
            for (CompraD x : carrito)
                listado.push_back(productoController.get(x.getCodProducto()).getNombre());
            menuListado(listado, 0, "Compra #" + to_string(compraController.size() + 1));
            if (menuConfirmar("Desea agregar una observacion a esta compra"))
            {
                cin.ignore();
                menuDatos({""}, inputs, 0, 0, "Observacion Compra #" + to_string(compraController.size() + 1));
                observacion = inputs[0];
            }

            for (CompraD x : carrito)
            {
                tempKardex.setCantidad(x.getCantidad());
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setCodProducto(x.getCodProducto());
                tempKardex.setCodProceso(createCode("CP", compraController.size(), 5));
                tempKardex.setComprobante(comprobante);
                tempKardex.setFechaDeEmision(fecha);
                tempKardex.setIsSalida(false);
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setMotivo("~~Compra " + to_string(cantComprobantes) + "~~");
                tempKardex.setObservacion(observacion);
                kardexController.add(tempKardex);
                kardexController.saveFile();
            }
            opt = 0;
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

void doVenta()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;

    long long int clienteDNI;
    int codProducto;
    int cantProducto;
    double montoProducto;
    string comprobante;
    string fecha;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(true);

    vector<CompraD> carrito;
    vector<kardex> kardexCarrito;
    CompraD tempCompraD;
    kardex tempKardex;

    menuListado({"Inicializando Venta..."}, 0, "Venta #" + to_string(ventaController.size() + 1), false);
    Sleep(1000);

    cout << "here" << endl;
    // FECHA
    if (menuConfirmar("Desea usar la fecha de hoy para registrar la Venta"))
    {
        cin.ignore();
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    }
    else
    {
        cin.ignore();
        do
        {
            cout << kardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }

    inputs.clear();
    // DNI
    do
    {
        inputs.clear();
        menuDatos({"DNI"}, inputs, 0, 0, "Datos del Proveedor Venta #" + to_string(ventaController.size() + 1)); // Clientes
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (inputs[0].size() != 8)
            menuError({"El DNI tiene 8 Dígitos"});
    } while (!esNumero(inputs[0]) || inputs[0].size() != 8 || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    clienteDNI = stoll(inputs[0]);
    inputs.clear();
    // COMPROBANTE VENTA PRODUCTO

    cin.ignore();
    inputs.clear();
    opt = menu("Comprobante Venta #" + to_string(ventaController.size() + 1), {"Boleta", "Factura"});
    switch (opt)
    {
    case 1:
        comprobante = createCode("BV", kardexController.getCantidadComprobanteVenta(true));
        break;
    case 2:
        comprobante = createCode("FV", kardexController.getCantidadComprobanteVenta(false));
        break;
    default:
        return;
        break;
    }

    do
    {
        opt = menu("_Carrito de Venta_ #" + to_string(ventaController.size() + 1), {"Agregar producto", "Eliminar Producto", "Mirar Carrito de Compra", "Finalizar Compra"});
        switch (opt)
        {
        case 1:
            // CODIGO PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Producto"}, inputs, 0, 0, "Producto Venta #" + to_string(ventaController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (stoi(inputs[0]) >= productoController.getNewCodProducto())
                    menuError({"Producto no registrado"});
            } while (!esNumero(inputs[0]) || stoi(inputs[0]) >= productoController.getNewCodProducto() || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                break;

            codProducto = stoi(inputs[0]);
            inputs.clear();

            // CANTIDAD PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Venta #" + to_string(ventaController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            cantProducto = stoi(inputs[0]);
            inputs.clear();

            // // PRECIO COMPRA PRODUCTO
            // do
            // {
            //     inputs.clear();
            //     menuDatos({"Costo Unitario"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
            //     if (!esNumero(inputs[0]))
            //         menuError({"Introduzca un valor numerico"});
            //     if (inputs[0].size() < 0)
            //         menuError({"Cantidad Invalida"});
            // } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            // if (aMinuscula(inputs[0]) == "salir")
            //     return;

            // montoProducto = stoi(inputs[0]);
            // inputs.clear();

            tempCompraD.setCodCompra(compraController.size());
            tempCompraD.setCodProducto(codProducto);
            tempCompraD.setCantidad(cantProducto);
            tempCompraD.setPrecio(productoController.get(codProducto).getPrecioUnitario());
            carrito.push_back(tempCompraD);
            break;
        case 2:
            do
            {
                listado.clear();
                for (CompraD x : carrito)
                    listado.push_back(productoController.get(x.getCodProducto()).getNombre());
                opt = menu("Suprimir Productos Venta #" + to_string(ventaController.size() + 1), listado);
                if (opt != 0 && opt != -1)
                {
                    carrito.erase(carrito.begin() + opt - 1);
                    listado.erase(listado.begin() + opt - 1);
                }
            } while (opt != 0);
            opt = 2;
            break;

        case 3:
            listado.clear();
            for (CompraD x : carrito)
                listado.push_back(productoController.get(x.getCodProducto()).getNombre());
            menuListado(listado, 0, "Venta #" + to_string(ventaController.size() + 1));
            break;

        case 4:
            listado.clear();
            for (CompraD x : carrito)
                listado.push_back(productoController.get(x.getCodProducto()).getNombre());
            menuListado(listado, 0, "Venta #" + to_string(ventaController.size() + 1));
            if (menuConfirmar("Desea agregar una observacion a esta Venta"))
            {
                cin.ignore();
                menuDatos({""}, inputs, 0, 0, "Observacion Venta #" + to_string(ventaController.size() + 1));
                observacion = inputs[0];
            }

            for (CompraD x : carrito)
            {
                tempKardex.setCantidad(x.getCantidad());
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setCodProducto(x.getCodProducto());
                tempKardex.setCodProceso(createCode("VT", compraController.size(), 5));
                tempKardex.setComprobante(comprobante);
                tempKardex.setFechaDeEmision(fecha);
                tempKardex.setIsSalida(true);
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setMotivo("~~Venta " + to_string(cantComprobantes) + "~~");
                tempKardex.setObservacion(observacion);
                kardexController.add(tempKardex);
                kardexController.saveFile();
            }
            opt = 0;
            break;
        case 0:
            if (!menuConfirmar("Seguro que desea cancelar la Venta"))
                opt = -1;
            break;
        default:
            break;
        }
    } while (opt != 0);
}

void doMovimiento()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;

    long long int clienteDNI;
    int codProducto;
    int cantProducto;
    double montoProducto;
    string comprobante;
    string codigoMovimiento;
    string fecha;
    string motivo;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(true);

    vector<CompraD> carrito;
    vector<kardex> kardexCarrito;
    CompraD tempCompraD;
    kardex tempKardex;

    // FECHA
    if (menuConfirmar("Desea usar la fecha de hoy para registrar el Movimiento"))
    {
        cin.ignore();
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    }
    else
    {
        cin.ignore();
        do
        {
            cout << kardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }

    inputs.clear();
    // DOCUMENTOS
    do
    {
        inputs.clear();
        menuDatos({"Documento"}, inputs, 0, 0, "Datos del Documento Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Clientes
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
    } while (!esNumero(inputs[0]) || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    clienteDNI = stoll(inputs[0]);
    inputs.clear();
    // COMPROBANTE VENTA PRODUCTO

    cin.ignore();
    inputs.clear();
    opt = menu("Comprobante Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Boleta de Venta Automatica", "Factura de Venta Automatica", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            cin.ignore();
            inputs.clear();
            menuDatos({"Comprobante de Compra"}, inputs, 0, 0, "Datos del Comprobante Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));
        comprobante = inputs[0];
    case 2:
        comprobante = createCode("BV", kardexController.getCantidadComprobanteVenta(true));
        break;
    case 3:
        comprobante = createCode("FV", kardexController.getCantidadComprobanteVenta(false));
        break;
    case 4:
        comprobante = "-";
    default:
        return;
        break;
    }

    // CODIGO MOVIMIENTO

    cin.ignore();
    inputs.clear();
    opt = menu("Codigo Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Automatico", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            cin.ignore();
            inputs.clear();
            menuDatos({"Codigo de Movimiento"}, inputs, 0, 0, "Codigo del Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));
    case 2:
        codigoMovimiento = createCode("MT", kardexController.getCantidadComprobante(false, true), 5);
        break;
    case 3:
        codigoMovimiento = "-";
    default:
        return;
        break;
    }

    //  PRODUCTO
    do
    {
        inputs.clear();
        menuDatos({"Producto"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (stoi(inputs[0]) >= productoController.getNewCodProducto())
            menuError({"Producto no registrado"});
    } while (!esNumero(inputs[0]) || stoi(inputs[0]) >= productoController.getNewCodProducto() || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    codProducto = stoi(inputs[0]);
    inputs.clear();

    bool isSalida = menuConfirmar("El movimiento es una reduccion en el inventario");

    // CANTIDAD PRODUCTO
    do
    {
        inputs.clear();
        cin.ignore();
        menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (inputs[0].size() < 0)
            menuError({"Cantidad Invalida"});
    } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    cantProducto = stoi(inputs[0]);
    inputs.clear();

    // PRECIO PRODUCTO

    cin.ignore();
    inputs.clear();
    opt = menu("Agregar precio al Producto, Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Automatico", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            inputs.clear();
            menuDatos({"Costo Unitario"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (!esNumero(inputs[0]))
                menuError({"Introduzca un valor numerico"});
            if (inputs[0].size() < 0)
                menuError({"Cantidad Invalida"});
        } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

        if (aMinuscula(inputs[0]) == "salir")
            return;
        montoProducto = stoi(inputs[0]);
    case 2:
        montoProducto=productoController.get(codProducto).getPrecioUnitario();
        break;
    case 3:
        montoProducto=0;
        break;
    default:
        return;
        break;
    }

    inputs.clear();

    tempCompraD.setCodCompra(compraController.size());
    tempCompraD.setCodProducto(codProducto);
    tempCompraD.setCantidad(cantProducto);
    tempCompraD.setPrecio(montoProducto);

    carrito.push_back(tempCompraD);

    ///////////////////////////////////////////////////////////

    cin.ignore();
    menuDatos({""}, inputs, 0, 0, "Motivo Movimiento #" + to_string(kardexController.getVector().size() + 1));
    motivo = inputs[0];

    if (menuConfirmar("Desea agregar una observacion a este Movimiento"))
    {
        cin.ignore();
        menuDatos({""}, inputs, 0, 0, "Observacion Movimiento #" + to_string(kardexController.getVector().size() + 1));
        observacion = inputs[0];
    }

    for (CompraD x : carrito)
    {
        tempKardex.setCantidad(x.getCantidad());
        tempKardex.setMontoUnitario(x.getPrecio());
        tempKardex.setCodProducto(x.getCodProducto());
        tempKardex.setCodProceso(codigoMovimiento);
        tempKardex.setComprobante(comprobante);
        tempKardex.setFechaDeEmision(fecha);
        tempKardex.setIsSalida(isSalida);
        tempKardex.setMontoUnitario(x.getPrecio());
        tempKardex.setMotivo(motivo);
        tempKardex.setObservacion(observacion);
        kardexController.add(tempKardex);
        kardexController.saveFile();
    }
}

int main(int argc, char *argv[])
{
    doMovimiento();
    cout << "Entré";
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