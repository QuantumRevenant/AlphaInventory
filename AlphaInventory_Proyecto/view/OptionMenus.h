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
        if(!doIniciarSesion(true, type))
            menuLogIn();
        break;
    case 2:
        doRegistrarse(false);
        menuLogIn();
        break;
    case 0:
        esquinarTexto("Cerrando Programa",1);
        for (int i = 0; i < 3; i++)
            {
                cout << ".";
                cout.flush();
                sleep(1);
            }
        Sleep(1000);
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
        menuUser();
        break;
    case 2:
        menuRecords();
        break;
    case 3:
        doRegistrarse(false);
        menuUser();
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
    case 0:
        menuMain();
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
    case 0:
        menuMain();
        break;
    }
}

#endif