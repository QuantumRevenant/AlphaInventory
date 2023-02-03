#ifndef OPTIONMENUS_H
#define OPTIONMENUS_H

#include <iostream>
#include <string>
#include "../model/FuncionesGenerales.h"

#define VOFFSET 5
#define HOFFSET 5

using namespace std;

/*

*/

// Option Menus
void menuLogIn();     // ✅
void menuMain();      // ✅
void menuUser();      // ✅
void menuInventory(); // ✅
void menuRecords();   // ✅

void menuLogIn()
{
    system("cls");
    string opt = "3";
    do
    {
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "-----SESIÓN-----" << endl
             << endl;
        cout << doTab(HOFFSET, "") << "--INICIO DE SESIÓN---" << doTab(2, "") << "[1]" << endl;
        cout << doTab(HOFFSET, "") << "--REGISTRO-----------" << doTab(2, "") << "[2]" << endl;
        cout << doTab(HOFFSET, "") << "--SALIR DEL PROGRAMA-" << doTab(2, "") << "[3]";
        doEndline(3);
        cout << doTab(HOFFSET + 1, "") << ">_ ";
        cin >> opt;

        if (esNumero(opt))
        {
            switch (stoi(opt))
            {
            case 1:
                // doLogin
                break;
            case 2:
                // doRegistro
                break;
            case 3:
                //
                break;
            default:
                cout << "Introduzca una opción valida [1-3]" << endl;
                break;
            }
        }
        else
        {
            cout << "Introduzca una opción valida [1-3]" << endl;
            opt = "0";
        }
    } while (stoi(opt) < 1 || stoi(opt) > 3);
}

void menuMain()
{
    system("cls");
    string opt = "5";
    do
    {
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "--MENU PRINCIPAL----" << endl
             << endl;
        cout << doTab(HOFFSET, "") << "--REGISTRAR VENTA----" << doTab(2, "") << "[1]" << endl;
        cout << doTab(HOFFSET, "") << "--"
             << "\"USERNAME\""
             << "\t-----" << doTab(2, "") << "[2]" << endl;
        cout << doTab(HOFFSET, "") << "--INVENTARIO---------" << doTab(2, "") << "[3]" << endl;
        cout << doTab(HOFFSET, "") << "--REGISTROS----------" << doTab(2, "") << "[4]" << endl;
        cout << doTab(HOFFSET, "") << "--SALIR DEL PROGRAMA-" << doTab(2, "") << "[5]" << endl;
        doEndline(3);
        cout << doTab(HOFFSET + 1, "") << ">_ ";
        cin >> opt;

        if (esNumero(opt))
        {
            switch (stoi(opt))
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
            case 5:
                cout<<"-<>-Hasta pronto-<>-"<<endl;
                break;
            default:
                cout << "Introduzca una opción valida [1-5]" << endl;
                break;
            }
        }
        else
        {
            cout << "Introduzca una opción valida [1-5]" << endl;
            opt = "0";
        }
    } while (stoi(opt) < 1 || stoi(opt) > 5);
}

void menuUser()
{
    system("cls");
    string opt = "6";
    do
    {
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "--MENU USUARIO-------" << endl
             << endl;
        cout << doTab(HOFFSET, "") << "--MODIFICAR PERFIL---" << doTab(2, "") << "[1]" << endl;
        cout << doTab(HOFFSET, "") << "--REGISTROS----------" << doTab(2, "") << "[2]" << endl;
        cout << doTab(HOFFSET, "") << "--REGISTRAR USUARIO--" << doTab(2, "") << "[3]" << endl;
        cout << doTab(HOFFSET, "") << "--ESTADO DE CAJA-----" << doTab(2, "") << "[4]" << endl;
        cout << doTab(HOFFSET, "") << "--CERRAR SESIÓN------" << doTab(2, "") << "[5]" << endl;
        cout << doTab(HOFFSET, "") << "--SALIR--------------" << doTab(2, "") << "[6]" << endl;
        doEndline(3);
        cout << doTab(HOFFSET + 1, "") << ">_ ";
        cin >> opt;

        if (esNumero(opt))
        {
            switch (stoi(opt))
            {
            case 1:
                // doModificarPerfil
                break;
            case 2:
                // menuRecords
                break;
            case 3:
                // doRegistrarse(false)
                break;
            case 4:
                // askEstadoCaja
                break;
            case 5:
                // doCerrarSesion
                break;
            case 6:
                menuMain();
                break;
            default:
                cout << "Introduzca una opción valida [1-6]" << endl;
                break;
            }
        }
        else
        {
            cout << "Introduzca una opción valida [1-6]" << endl;
            opt = "0";
        }

    } while (stoi(opt) < 1 || stoi(opt) > 6);
}

void menuInventory()
{
    system("cls");
    string opt = "4";
    do
    {
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "--MENU INVENTARIO-------" << endl
             << endl;
        cout << doTab(HOFFSET, "") << "--AÑADIR PRODUCTOS---" << doTab(2, "") << "[1]" << endl;
        cout << doTab(HOFFSET, "") << "--CONSULTAR PRODUCTO-" << doTab(2, "") << "[2]" << endl;
        cout << doTab(HOFFSET, "") << "--MODIFICAR PRODUCTO-" << doTab(2, "") << "[3]" << endl;
        cout << doTab(HOFFSET, "") << "--SALIR--------------" << doTab(2, "") << "[4]" << endl;
        doEndline(3);
        cout << doTab(HOFFSET + 1, "") << ">_ ";
        cin >> opt;

        if (esNumero(opt))
        {
            switch (stoi(opt))
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
        else
        {
            cout << "Introduzca una opción valida [1-4]" << endl;
            opt = "0";
        }
    } while (stoi(opt) < 1 || stoi(opt) > 4);
}

void menuRecords()
{
    system("cls");
    string opt = "4";
    do
    {
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "--MENU INVENTARIO-------" << endl
             << endl;
        cout << doTab(HOFFSET, "") << "--ESTADO DE CAJA-------" << doTab(2, "") << "[1]" << endl;
        cout << doTab(HOFFSET, "") << "--REGISTROS PERSONALES-" << doTab(2, "") << "[2]" << endl;
        cout << doTab(HOFFSET, "") << "--BUSCAR REGISTROS-----" << doTab(2, "") << "[3]" << endl;
        cout << doTab(HOFFSET, "") << "--SALIR----------------" << doTab(2, "") << "[4]" << endl;
        doEndline(3);
        cout << doTab(HOFFSET + 1, "") << ">_ ";
        cin >> opt;

        if (esNumero(opt))
        {
            switch (stoi(opt))
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
        else
        {
            cout << "Introduzca una opción valida [1-4]" << endl;
            opt = "0";
        }
    } while (stoi(opt) < 1 || stoi(opt) > 4);
}

#endif