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
    menuLogIn();
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
    string opt;
    int docSize;
    bool loged = false;

    do
    {
        system("cls");
        if (!start)
        {
            doEndline(VOFFSET);
            cout << doTab(HOFFSET + 1, "") << "-----REGISTRO------" << endl
                 << endl;
            cout << doTab(HOFFSET + 1, "") << "--TIPO DE USUARIO--" << endl
                 << endl
                 << doTab(HOFFSET, "") << "--VENDEDOR---------------" << doTab(1, "") << "[1]" << endl
                 << doTab(HOFFSET, "") << "--SUPERVISOR-------------" << doTab(1, "") << "[2]" << endl
                 << doTab(HOFFSET, "") << "--ADMINISTRADOR----------" << doTab(1, "") << "[3]" << endl
                 << doTab(HOFFSET, "") << "--CANCELAR---------------" << doTab(1, "") << "[4]" << endl
                 << endl;
            getValue(doTab(HOFFSET + 1, "") + "Ingrese opcion[1-3]: \n" + doTab(HOFFSET + 1, "") + ">_", &opt);

            if (esNumero(opt))
            {
                switch (stoi(opt))
                {
                case 1:
                    system("cls");
                    doEndline(VOFFSET);
                    cout << doTab(HOFFSET, "") << "-NECESITAS INICIAR SESIÓN COMO SUPERVISOR O ADMINISTRADOR-" << endl;
                    sleep(3);
                    loged = doIniciarSesion(false, type);
                    if (loged && (type == "Administrador" || type == "Supervisor"))
                        tipoUsuario = "Vendedor";
                    else
                        cout << doTab(HOFFSET + 1, "") << "##=CANCELASTE EL REGISTRO##=" << endl;
                    tipoUsuario = "Cancelar";
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    doEndline(VOFFSET);
                    cout << doTab(HOFFSET, "") << "-NECESITAS INICIAR SESIÓN COMO ADMINISTRADOR-" << endl;
                    sleep(3);
                    loged = doIniciarSesion(false, type);
                    if (loged && type == "Administrador")
                        tipoUsuario = "Supervisor";
                    else
                        cout << doTab(HOFFSET+1, "") << "##=CANCELASTE EL REGISTRO##=" << endl;
                    tipoUsuario = "Cancelar";
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    doEndline(VOFFSET);
                    cout << doTab(HOFFSET, "") << "-NECESITAS INICIAR SESIÓN COMO ADMINISTRADOR-" << endl;
                    sleep(3);
                    loged = doIniciarSesion(false, type);
                    if (loged && type == "Administrador")
                        tipoUsuario = "Administrador";
                    else
                        cout << doTab(HOFFSET + 1, "") << "##=CANCELASTE EL REGISTRO##=" << endl;
                    tipoUsuario = "Cancelar";
                    system("pause");
                    break;
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
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
                system("cls");
                opt = "0";
            }
        }
        else
        {
            doEndline(VOFFSET - 3);
            cout << doTab(HOFFSET, "") << "-------NO TENEMOS REGISTRO DE ADMINISTRADORES-------" << endl
                 << doTab(HOFFSET, "") << "-REGISTRA UN NUEVO ADMINISTRADOR ANTES DE CONTINUAR-" << endl;
            sleep(1);
            opt = "3";
            tipoUsuario = "Administrador";
            system("pause");
        }
    } while (stoi(opt) < 1 || stoi(opt) > 4);
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
            if (esNumero(opt))
            {
                switch (stoi(opt))
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
            }
            else
            {
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
                system("cls");
                opt = "0";
            }
        } while (stoi(opt) < 1 || stoi(opt) > 4);

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
void doModificarPerfil(string key)
{
    string temporal;
    int opt;
    Usuario objUser = userController.getUsuario(key);
    do
    {
        temporal = "3136435667";
        system("cls");
        cout << "--EDITAR PERFIL------------" << endl;
        cout << "--Usuario---------------[1]" << endl;
        cout << "--Nombre----------------[2]" << endl;
        cout << "--Apellidos-------------[3]" << endl;
        cout << "--Contraseña------------[4]" << endl;
        cout << "--Documento-------------[5]" << endl;
        cout << "--Guardar Cambios-------[6]" << endl;
        cout << "--Cancelar Cambios------[7]" << endl;
        getValue("Ingrese opcion[1-6]: ", &opt);
        switch (opt)
        {
        case 1:
            do
            {
                if (temporal != "3136435667")
                    cout << "##[USUARIO YA EXISTE, ESCOGE OTRO NOMBRE]##" << endl;
                getValue("Nombre de usuario: ", &temporal);
            } while (userController.validarUsuarioNoExiste(temporal));
            if (confirmar("que \"" + temporal + "\" sea su nuevo nombre de usuario?"))
                objUser.setUsername(temporal);
            break;
        case 2:
            getValue("Nombre: ", &temporal);
            if (confirmar("que \"" + temporal + "\" sea su nombre?"))
                objUser.setNombre(temporal);
            break;
        case 3:
            cin.ignore();
            cout << "Apellidos: ";
            getline(cin, temporal);
            if (confirmar("que \"" + temporal + "\" sea sus apellidos?"))
                objUser.setApellidos(temporal);
            break;
        case 4:
            objUser.modifyContrasena();
            break;
        case 5:
            objUser.modifyDocumento();
            break;
        case 6:
            if (confirmar("guardar los cambios", "Deberás reiniciar la sesión."))
            {
                userController.modify(objUser, userController.getUsuario(key, true));
                userController.archGrabarDatos();
                progController.closeSesion();
            }
            cout << "Cancelando los cambios...";
            break;
        case 7:
            cout << "Cancelando los cambios...";
            break;
        default:
            cout << "Ingrese una opción valida[1-7]" << endl;
            system("pause");
            break;
        }
    } while (opt != 6 && opt != 7);
}
bool doIniciarSesion(bool opt, string &type)
{
    string username,
        contrasena;
    int contador = 0;
    bool resultado = false;

    do
    {
        system("cls");
        doEndline(VOFFSET);
        cout << doTab(HOFFSET + 1, "") << "-----INICIO DE SESIÓN-----" << endl;
        cout << doTab(HOFFSET, "") << "--INTRODUCE 'SALIR' PARA CERRAR---" << endl;
        cout << doTab(HOFFSET, "") << "USERNAME: " << endl
             << doTab(HOFFSET, "") << ">_ ";
        cin >> username;
        if (aMinuscula(username) == "salir")
            break;
        cout << doTab(HOFFSET, "") << "CONTRASEÑA: " << endl
             << doTab(HOFFSET, "") << ">_ ";
        cin >> contrasena;
        if (aMinuscula(contrasena) == "salir")
            break;
        resultado = userController.validarSesion(username, contrasena);
        if (resultado)
        {
            system("cls");
            doEndline(VOFFSET);
            cout << doTab(HOFFSET, "") << "Iniciando Sesión"; // Agregar el inicio de sesión
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                cout.flush();
                sleep(1);
            }
            cout << endl;
        }
        else
        {
            /*
            INICIO DE SESION INCORRECTO

            Si(username && contrasena no encontrados)
                No tenemos username y contraseña en nuestra base de datos
            else si(username no encontrado)
                Username Incorrecto
            else
                Contrasena Incorrecta

            contador++
            */
            cout << doTab(HOFFSET-1, "") << "Username y contraseña incorrectos y/o no registrados en nuestra base de datos." << endl;
            cout << doTab(HOFFSET-1, "");
            system("pause");
            contador++;
        }
    } while (!resultado && contador < 3);

    if (contador >= 3)
    {
        cout << doTab(HOFFSET-1, "") << "Límite de intentos alcanzado, volviendo al menú principal..." << endl;
        system("pause");
        return false;
    }

    if (resultado && contador < 3)
    {
        bool isAdm = false, isSupervisor = false;
        Usuario tempUser;
        tempUser = userController.getUsuario(username, contrasena);
        if (tempUser.getTipoUsuario() == "Administrador")
            isAdm = isSupervisor = true;
        else if (tempUser.getTipoUsuario() == "Supervisor")
        {
            isAdm = false;
            isSupervisor = true;
        }
        else
            isAdm = isSupervisor = false;

        cout << doTab(HOFFSET, "") << "Sesion iniciada" << endl;
        sleep(1);
        cout << doTab(HOFFSET, "") << "Bienvenido " << username << endl;
        sleep(1);
        if (opt)
        {
            progController.openSesion(userController.getUsuario(username, contrasena).getCodigo(), isSupervisor, isAdm);
            menuMain();
            return true;
        }
        else
        {
            if (isAdm)
                type = "Administrador";
            else if (isSupervisor)
                type = "Supervisor";
            system("pause");
            return true;
        }
    }
    return false;
}
void doCerrarSesion()
{
    progController.closeSesion();
    menuLogIn();
}