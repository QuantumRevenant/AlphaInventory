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
    system("cls");
    int opt;
    string type;

    vector<string> options = {"Inicio de sesion", "Registro"};
    opt = menu("BIENVENIDO", options);

    switch (opt)
    {
    case 1:
        doIniciarSesion(true, type);
        break;
    case 2:
        doRegistrarse(false);
        break;
    case 0:
        // Salir
        break;
    default:
        cout << "Error, opcion no válida" << endl;
        break;
    }
}

void menuMain()
{
    system("cls");
    int opt;
    vector<string> options = {"Registrar venta", "\"" + userController.getUsuario(progController.getSesionKey()).getUsername() + "\"", "Inventario", "Registro de ventas"};
    opt = menu("MENU PRINCIPAL", options);
    switch (opt)
    {
    case 1:
        // doVenta
        break;
    case 2:
        menuUser();
        break;
    case 3:
        menuInventory();
        break;
    case 4:
        menuRecords();
        break;
    case 0:
        esquinarTexto("-<>-Hasta pronto-<>-", 1);
        break;
    }
}
void menuUser()
{
    system("cls");
    int opt;
    vector<string> options = {"Modificar Perfil", "Registros", "Registrar Usuario", "Estado de Caja", "Cerrar Sesión"};
    opt = menu("MENU USUARIO", options);

    switch (opt)
    {
    case 1:
        doModificarPerfil(progController.getSesionKey());
        break;
    case 2:
        menuRecords();
        break;
    case 3:
        doRegistrarse(false);
        break;
    case 4:
        // askEstadoCaja
        break;
    case 5:
        doCerrarSesion();
        break;
    case 0:
        menuMain();
        break;
    default:
        cout << "Introduzca una opción valida [1-6]" << endl;
        break;
    }
}

void menuInventory()
{
    system("cls");
    int opt;
    vector<string> options = {"Registrar Compra", "Consultar Inventario", "Modificar Datos de producto"}; // Añadir Marca
    opt = menu("MENU INVENTARIO", options);
    switch (opt)
    {
    case 1:
        // doAddInventario
        break;
    case 2:
        // askInventario
        break;
    case 3:
        // changeDataInventario
        break;
    case 4:
        menuMain();
        break;
    default:
        cout << "Introduzca una opción valida [1-4]" << endl;
        break;
    }
}

void menuRecords()
{
    system("cls");
    int opt;
    vector<string> options = {"Estado de Caja", "Registros Personales", "Buscar Registros"}; // Carritos de compra, etc
    opt = menu("MENU REGISTROS", options);

    switch (opt)
    {
    case 1:
        // askEstadoCaja
        break;
    case 2:
        // doConsultarRegistro
        break;
    case 3:
        // doConsultarRegistro
        break;
    case 4:
        menuMain();
        break;
    default:
        cout << "Introduzca una opción valida [1-4]" << endl;
        break;
    }
}

#endif