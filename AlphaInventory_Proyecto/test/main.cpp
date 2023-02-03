#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../model/Usuario.cpp"
#include "../controller/usuarioController.h"
#include "../controller/programController.h"
#include "../model/FuncionesGenerales.h"
#include "OptionMenus.h"

#define VOFFSET 5
#define HOFFSET 5

using namespace std;

usuarioController userController;
programController progController;

/*
1) INICIO DE SESIÓN
    *>REGISTRARSE
    >INICIAR SESION
2) MENU PRINCIPAL
    >REGISTRAR VENTA
    >/[USUARIO]/
    >INVENTARIO (MODIFICAR Y CONSULTAR)
    >REGISTROS (PERSONALES{DIA, GENERAL} O OTRO USUARIO{SUPERVISOR PARA REVISAR DE VENDEDORES Y ADM PARA REVISAR DE SUPERVISORES} Y VENTAS)
3) USUARIO
    >MODIFICAR
    >REGISTROS
    *>REGISTRARSE
    >ESTADO DE CAJA
    >CERRAR SESION
4) INVENTARIO
    >AÑADIR
    >CONSULTAR
    >MODIFICAR
5) REGISTROS
    >ESTADO DE CAJA
    >VENTAS PERSONALES
    >CONSULTAR OTROS
*/

// Cuenta y usuario
void doRegistrarse(bool);
bool doIniciarSesion(bool, string &);
void doCerrarSesion();
void doModificarPerfil(string);

// Ventas y Registros
void doVenta();
void askEstadoCaja();
void doConsultarRegistro();

// Inventario
void doAddInventario();
void askInventario();
void changeDataInventario();

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // Validar si hay administrador en el registro, sino:
    //  doRegistrarse(true)

    // menuLogIn();
    menuMain();
    cout << endl
         << endl
         << doTab(2, "") << "##Cerrando el programa##" << endl;
    return 0;
}

void doRegistrarse(bool start)
{
    
    string type;
    string username;
    string nombre;
    string apellidos;
    string strInput;
    int numDocumento;
    string tipoUsuario;
    string tipoDocumento;
    string contrasena;
    string contrasenaConfi;
    int opt;
    int docSize;
    bool admLoged = false;

    do
    {
        if (!start)
        {
            cout << "--TIPO DE USUARIO-----------" << endl
                 << "--CLIENTE----------------[1]" << endl
                 << "--VENDEDOR---------------[2]" << endl
                 << "--ADMINISTRADOR----------[3]" << endl
                 << "--CANCELAR---------------[4]" << endl;
            getValue("Ingrese opcion[1-3]: ", &opt);
            if (opt == 2 || opt == 3)
            {
                cout << "Para crear un usuario de vendedor o administrador, debe iniciar sesion como administrador" << endl;
                admLoged = doIniciarSesion(false, type);
            }
            switch (opt)
            {
            case 1:
                tipoUsuario = "Cliente";
                break;
            case 2:
                if (admLoged && type == "Administrador")
                    tipoUsuario = "Vendedor";
                else
                {
                    opt = -1;
                    cout << "ERROR: La sesión iniciada no es un Administrador..." << endl;
                    tipoUsuario = "Cancelar";
                    system("pause");
                }
                break;
            case 3:
                if (admLoged && type == "Administrador")
                    tipoUsuario = "Administrador";
                else
                {
                    opt = -1;
                    cout << "ERROR: La sesión iniciada no es un Administrador..." << endl;
                    tipoUsuario = "Cancelar";
                    system("pause");
                }
                break;
            case 4:
                tipoUsuario = "Cancelar";
                break;
            default:
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
                system("cls");
            }
        }
        else
        {
            cout << "--NO TENEMOS REGISTRO DE ADMINISTRADORES--------------" << endl
                 << "--REGISTRA UN NUEVO ADMINISTRADOR ANTES DE CONTINUAR--" << endl;
            opt = 3;
            tipoUsuario = "Administrador";
            system("pause");
        }
    } while (opt != 1 && opt != 2 && opt != 3 && opt != 4);
    if (tipoUsuario != "Cancelar")
    {
        system("cls");
        getValue("Nombre de usuario: ", &username);
        getValue("Nombre: ", &nombre);

        cin.ignore();
        cout << "Apellidos: ";
        getline(cin, apellidos);
        do
        {
            system("cls");
            cout << "--TIPO DE DOCUMENTO---------" << endl;
            cout << "--DNI--------------------[1]" << endl;
            cout << "--CARNET EXT-------------[2]" << endl;
            cout << "--PASAPORTE--------------[3]" << endl;
            cout << "--RUC--------------------[4]" << endl;
            getValue("Ingrese opcion[1-4]: ", &opt);
            switch (opt)
            {
            case 1:
                tipoDocumento = "DNI";
                docSize = 8;
                break;
            case 2:
                tipoDocumento = "CE";
                docSize = 12;
                break;
            case 3:
                tipoDocumento = "PASAPORTE";
                docSize = 12;
                break;
            case 4:
                tipoDocumento = "RUC";
                docSize = 11;
                break;
            default:
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
            }
        } while (opt != 1 && opt != 2 && opt != 3 && opt != 4);

        strInput = "0";
        do
        {
            system("cls");
            cout << tipoDocumento << endl;
            if (!esNumero(strInput))
            {
                cout << "===[INTRODUCE UN VALOR NUMERICO]===" << endl;
            }
            getValue("Numero de documento: ", &strInput);
            if ((int)strInput.size() != docSize)
            {
                cout << "Los documentos tipo " << tipoDocumento << " deben contener " << docSize << " digitos" << endl;
                cout << "VUELVA A INGRESAR SU NUMERO DE DOCUMENTO" << endl;
                system("pause");
            }
        } while (!esNumero(strInput) || (int)strInput.size() != docSize);
        numDocumento = stoi(strInput);
        do
        {
            system("cls");
            getValue("Contrasena(minimo 8 caracteres): ", &contrasena);
            system("cls");
            getValue("Confirmar contrasena: ", &contrasenaConfi);
            if (contrasena.size() < 8)
            {
                cout << "La contrasena debe tener minimo 8 caracteres" << endl;
                cout << "VUELVA A INGRESAR UNA CONTRASENA" << endl;
                system("pause");
            }
            else if (contrasena != contrasenaConfi)
            {
                cout << "Las contrasenas no son iguales" << endl;
                cout << "VUELVA A INGRESAR UNA CONTRASENA" << endl;
                system("pause");
            }
        } while (contrasena != contrasenaConfi || contrasena.length() < 8);

        Usuario objUser(username, objUser.encriptar(contrasena), nombre, apellidos, tipoDocumento, numDocumento, tipoUsuario);

        userController.add(objUser);
        objUser.listarDatos(); // BORRAR VERSION FINAL - SOLO DEBUG
        system("cls");
        userController.archGrabarDatos();
    }
}

bool doIniciarSesion()
{

}
