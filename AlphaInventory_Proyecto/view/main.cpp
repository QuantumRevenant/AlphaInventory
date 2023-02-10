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
#include "../controller/Encrypter/sha256.cpp"

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
    int docSize;
    bool loged = false;
    int opt;

    int sizeY = 3, e = 0;

    system("cls");
    if (!start)
    {
        vector<string> options = {"VENDEDOR", "SUPERVISOR", "ADMINISTRADOR"}; // Carritos de compra, etc
        opt = menu("REGISTRO - TIPO DE USUARIO", options);
        switch (opt)
        {
        case 1:

            system("cls");
            dibujarCuadro();
            centrarTexto("~\t-NECESITAS INICIAR SESIÓN COMO SUPERVISOR O ADMINISTRADOR-\t~");
            Sleep(1000);

            loged = doIniciarSesion(false, type);

            if (loged && (type == "Administrador" || type == "Supervisor"))
                tipoUsuario = "Vendedor";
            else
            {
                system("cls");
                dibujarCuadro();
                centrarTexto("~\t-CANCELASTE EL REGISTRO-\t~");
                tipoUsuario = "Cancelar";
                esquinarTexto("", 1, false, true, false);
                system("pause");
            }
            break;
        case 2:
            system("cls");
            dibujarCuadro();
            centrarTexto("~\t-NECESITAS INICIAR SESIÓN COMO ADMINISTRADOR-\t~");
            Sleep(1000);

            loged = doIniciarSesion(false, type);

            if (loged && type == "Administrador")
                tipoUsuario = "Supervisor";
            else
            {
                system("cls");
                dibujarCuadro();
                centrarTexto("~\t-CANCELASTE EL REGISTRO-\t~");
                tipoUsuario = "Cancelar";
                esquinarTexto("", 1, false, true, false);
                system("pause");
            }
            break;
        case 3:
            system("cls");
            dibujarCuadro();
            centrarTexto("~\t-NECESITAS INICIAR SESIÓN COMO ADMINISTRADOR-\t~");
            Sleep(1000);

            loged = doIniciarSesion(false, type);

            if (loged && type == "Administrador")
                tipoUsuario = "Administrador";
            else
            {
                system("cls");
                dibujarCuadro();
                centrarTexto("~\t-CANCELASTE EL REGISTRO-\t~");
                tipoUsuario = "Cancelar";
                esquinarTexto("", 1, false, true, false);
                system("pause");
            }
            break;
        case 0:
            tipoUsuario = "Cancelar";
            break;
        };
        if (tipoUsuario == "Cancelar")
            return;

        system("cls");
        dibujarCuadro();
        alinearXTexto("Nombre de usuario: ", 0, true, 30, (-sizeY + e), true);
        e++;
        alinearXTexto("Nombres: ", 0, true, 30, (-sizeY + e), true);
        e++;
        alinearXTexto("Apellidos: ", 0, true, 30, (-sizeY + e), true);
        e++;

        e = 0;
        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        cin >> username;
        e++;

        cin.ignore();
        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        getline(cin, nombre);
        e++;

        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        getline(cin, apellidos);
        e++;

        options = {"DNI", "CARNET EXTRANJERIA (CE)", "PASAPORTE", "RUC"}; // Carritos de compra, etc
        opt = menu("REGISTRO - TIPO DE USUARIO", options);

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
        case 0:
            tipoDocumento = "Cancelar";
            break;
        }

        if (tipoDocumento == "Cancelar")
            return;

        strInput = "0";
        do
        {
            sizeY = 4;
            e = 0;
            system("cls");
            dibujarCuadro();
            centrarTexto("_" + tipoDocumento + "_", 0, true, true, 0, (-sizeY + e));
            e++;
            centrarTexto("['Salir' para salir]", 0, true, true, 0, (-sizeY + e));
            e += 2;
            alinearXTexto("Numero de documento: ", 0, true, 30, (-sizeY + e));
            alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
            cin >> strInput;

            if (aMinuscula(strInput) == "salir")
                return;

            if ((int)strInput.size() != docSize)
            {
                sizeY = 3;
                e = 0;
                system("cls");
                dibujarCuadro();
                system("color 4f");
                centrarTexto("~\t-Los documentos tipo " + tipoDocumento + " deben contener " + to_string(docSize) + " digitos-\t~", 0, true, true, 0, (-sizeY + e));
                e += 2;
                centrarTexto("~\tVUELVA A INGRESAR SU NUMERO DE DOCUMENTO\t~", 0, true, true, 0, (-sizeY + e));
                Sleep(1000);
                char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
                system(color);
            }
            if (!esNumero(strInput))
            {
                system("cls");
                dibujarCuadro();
                system("color 4f");
                centrarTexto("~\t[[INTRODUCE UN VALOR NUMERICO]]\t~");
                Sleep(1000);
                char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
                system(color);
            }
        } while (!esNumero(strInput) || (int)strInput.size() != docSize);

        numDocumento = stoi(strInput);

        int sizePass;
        do
        {
            sizeY = 3;
            e = 0;
            system("cls");
            dibujarCuadro();
            alinearXTexto("Contraseña: ", 0, true, 30, (-sizeY + e), true);
            e += 2;
            alinearXTexto("Repetir contraseña: ", 0, true, 30, (-sizeY + e), true);

            e = 0;
            alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
            strInput = enterContrasena();
            sizePass = strInput.size();
            contrasena = sha256(strInput);
            strInput = "";
            e += 2;

            alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
            contrasenaConfi = sha256(enterContrasena());
            e++;
            if (sizePass < 8)
            {
                sizeY = 3;
                e = 0;
                system("cls");
                dibujarCuadro();
                system("color 4f");
                centrarTexto("~\t-La contrasena debe tener minimo 8 caracteres-\t~", 0, true, true, 0, (-sizeY + e));
                e += 2;
                centrarTexto("~\tVUELVA A INGRESAR UNA CONTRASENA\t~", 0, true, true, 0, (-sizeY + e));
                Sleep(1000);
                char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
                system(color);
            }
            else if (contrasena != contrasenaConfi)
            {
                sizeY = 3;
                e = 0;
                system("cls");
                dibujarCuadro();
                system("color 4f");
                centrarTexto("~\t-Las contrasenas no son iguales-\t~", 0, true, true, 0, (-sizeY + e));
                e += 2;
                centrarTexto("~\tVUELVA A INGRESAR UNA CONTRASENA\t~", 0, true, true, 0, (-sizeY + e));
                Sleep(1000);
                char color[] = {'c', 'o', 'l', 'o', 'r', ' ', baseColor[0], baseColor[1], '\0'};
                system(color);
            }
        } while (contrasena != contrasenaConfi || sizePass < 8);

        Usuario objUser(userController.getCodigo(),username, contrasena, nombre, apellidos, tipoDocumento, numDocumento, tipoUsuario);

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
            cout << doTab(HOFFSET - 1, "") << "Username y contraseña incorrectos y/o no registrados en nuestra base de datos." << endl;
            cout << doTab(HOFFSET - 1, "");
            system("pause");
            contador++;
        }
    } while (!resultado && contador < 3);

    if (contador >= 3)
    {
        cout << doTab(HOFFSET - 1, "") << "Límite de intentos alcanzado, volviendo al menú principal..." << endl;
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