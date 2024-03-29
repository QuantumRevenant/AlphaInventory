#ifndef OPTIONMENUS_CPP
#define OPTIONMENUS_CPP

#include <iostream>
#include <string>
#include "../model/FuncionesGenerales.h"
#include "Funciones.h"

#define VOFFSET 5
#define HOFFSET 5

using namespace std;

/*

*/

void menuLogIn()
{
    doActualizarInventario();
    system("cls");
    int opt;
    string type;

    vector<string> options = {"Inicio de sesion", "Registro"};
    opt = menu("BIENVENIDO", options);

    switch (opt)
    {
    case 1:
        if (!doIniciarSesion(true, type))
            menuLogIn();
        break;
    case 2:
        doRegistrarse(false);
        menuLogIn();
        break;
    case 0:
        esquinarTexto("Cerrando Programa", 1);
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            cout.flush();
            Sleep(1);
        }
        Sleep(1000);
        break;
    }
}
void menuMain()
{
    doActualizarInventario();
    system("cls");
    int opt;
    vector<string> options = {"Registrar venta", "\"" + userController.getUsuario(progController.getSesionKey()).getUsername() + "\"", "Inventario", "Otros"};
    opt = menu("MENU PRINCIPAL", options);
    switch (opt)
    {
    case 1:
        doVenta();
        menuMain();
        break;
    case 2:
        menuUser();
        break;
    case 3:
        menuInventory();
        break;
    case 4:
        menuOthers();
        break;
    case 0:
        esquinarTexto("-<>-Hasta pronto-<>-", 1);
        break;
    }
}
void menuUser()
{
    doActualizarInventario();
    system("cls");
    int opt;
    vector<string> options = {"Modificar Perfil" /*, "Registros"*/, "Registrar Usuario", "Estado de Caja", "Cerrar Sesi�n"};
    opt = menu("MENU USUARIO", options);

    switch (opt)
    {
    case 1:
        doModificarPerfil(progController.getSesionKey());
        menuUser();
        break;
    /*case 2:
        menuRecords();
        break;*/
    case 2:
        doRegistrarse(false);
        menuUser();
        break;
    case 3:
        askEstadoCaja();
        menuUser();
        break;
    case 4:
        doCerrarSesion();
        break;
    case 0:
        menuMain();
        break;
    }
}

void menuInventory()
{
    doActualizarInventario();
    system("cls");
    int opt;
    vector<string> options = {"Registrar Compra", "Consultar Inventario", "Modificar Datos de producto", "Anadir Nuevo Producto", "Anadir Nueva Marca"};
    do
    {
        opt = menu("MENU INVENTARIO", options);
        switch (opt)
        {
        case 1:
            doCompra();
            menuInventory();
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
        case 0:
            menuMain();
            break;
        default:
            marcaController.saveFile();
            break;
        }
    } while (opt != 0);
}

void menuRecords()
{
    doActualizarInventario();
    system("cls");
    int opt;
    vector<string> options = {"Estado de Caja", "Registros Personales", "Buscar Registros"}; // Carritos de compra, etc
    do
    {
        opt = menu("MENU REGISTROS", options);
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
            menuMain();
            break;
        }
    } while (opt != 0);
}

void menuOthers()
{
    doActualizarInventario();
    system("cls");
    int opt;
    vector<string> options = {"Registrar Movimiento", "Registrar Cliente", "Registrar Proveedor", "Retiro de Caja"}; // Carritos de compra, etc
    do
    {
        opt = menu("MENU REGISTROS", options);
        switch (opt)
        {
        case 1:
            doMovimiento();
            break;
        case 2:
            doRegistrarTercero(true, -1);
            break;
        case 3:
            doRegistrarTercero(false, -1);
            break;
        case 4:
            doRegistrarRetiroCaja();
            break;
        case 0:
            menuMain();
            break;
        }
    } while (opt != 0);
}

#endif