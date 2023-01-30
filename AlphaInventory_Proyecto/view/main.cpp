#include <iostream>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../model/Usuario.cpp"
#include "../controller/usuarioController.h"
#include "../controller/programController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

usuarioController userController;
programController progController;

void menuLogin();
bool iniciarSesion(bool, string &);
void registrarse();
void menuUsuario(string, string);
void modifyPerfil(string);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    menuLogin();
    return 0;
}

void menuLogin()
{
    string type;
    int opt;
    do
    {
        system("cls");
        cout << "--FARMACIA MIRIAM------------" << endl;
        cout << "--Iniciar Sesion----------[1]" << endl;
        cout << "--Registrarse-------------[2]" << endl;
        cout << "--Continuar como Invitado-[3]" << endl;
        cout << "--Salir-------------------[4]" << endl;
        getValue("Ingrese opcion[1-4]: ", &opt);
        switch (opt)
        {
        case 1:
            system("cls");
            iniciarSesion(true, type);
            break;
        case 2:
            system("cls");
            registrarse();
            break;
        case 3:
            menuUsuario("Invitado", NULL);
            break;
        case 4:
            cout << "#####Gracias por usar nuestro servicio#####";
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
        }
    } while (opt != 4);
}
bool iniciarSesion(bool opt, string &type)
{
    string username,
        contrasena;
    int contador = 0;
    bool resultado = false;

    do
    {
        cout << "--INTRODUCE 'SALIR' PARA CERRAR---" << endl;
        cout << "--INICIO DE SESIÓN----------------" << endl;
        cout << "USERNAME: ";
        cin >> username;
        if (aMinuscula(username) == "salir")
            break;
        cout << "CONTRASEÑA: ";
        cin >> contrasena;
        if (aMinuscula(contrasena) == "salir")
            break;
        resultado = userController.validarSesion(username, contrasena);
        if (resultado)
        {
            system("cls");
            cout << "Iniciando Sesión"; // Agregar el inicio de sesión
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
            cout << "Username y contraseña incorrectos y/o no registrados en nuestra base de datos." << endl;
            contador++;
        }
    } while (!resultado || contador >= 3);

    if (resultado && contador < 3)
    {
        bool isAdm = false, isSell = false;
        Usuario tempUser;
        tempUser = userController.getUsuario(username, contrasena);
        if (tempUser.getTipoUsuario() == "Administrador")
            isAdm = isSell = true;
        else if (tempUser.getTipoUsuario() == "Administrador")
        {
            isAdm = false;
            isSell = true;
        }
        else
            isAdm = isSell = false;

        if (opt)
        {
            progController.openSesion(userController.getUsuario(username, contrasena).getCodigo(), isSell, isAdm);
            cout << "Sesion iniciada" << endl;
            sleep(1);
            cout << "Bienvenido " << username;
            sleep(1);
            menuUsuario(userController.getUsuario(username, contrasena).getTipoUsuario(), userController.getUsuario(username, contrasena).getCodigo());
            return true;
        }
        else
        {
            type = tempUser.getTipoUsuario();
            return true;
        }
    }
    return NULL;
}
void registrarse()
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

    do
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
            iniciarSesion(false, type);
            break;
        }
        switch (opt)
        {
        case 1:
            tipoUsuario = "Cliente";
            break;
        case 2:
            tipoUsuario = "Vendedor";
            break;
        case 3:
            tipoUsuario = "Administrador";
            break;
        case 4:
            tipoUsuario = "Cancelar";
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
            system("cls");
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
            if (strInput.size() != docSize)
            {
                cout << "Los documentos tipo " << tipoDocumento << " deben contener " << docSize << " digitos" << endl;
                cout << "VUELVA A INGRESAR SU NUMERO DE DOCUMENTO" << endl;
                system("pause");
            }
        } while (!esNumero(strInput) || strInput.size() != docSize);
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
        objUser.listarDatos();
        system("cls");
        iniciarSesion(true, type);
    }
}
void menuUsuario(string userType, string key)
{
    int opt;
    if (userType == "Invitado")
    {
        do
        {
            system("cls");
            cout << "--FARMACIA MIRIAM------------" << endl;
            cout << "--Comprar-----------------[1]" << endl;
            cout << "--Consultar Stock---------[2]" << endl;
            cout << "--Registrarse-------------[3]" << endl;
            cout << "--Salir-------------------[4]" << endl;
            getValue("Ingrese opcion[1-4]: ", &opt);
            switch (opt)
            {
            case 1:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 3:
                system("cls");
                registrarse();
                break;
            case 4:
                break;
            default:
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
            }
        } while (opt != 4);
    }
    else if (userType == "Cliente")
    {
        do
        {
            system("cls");
            cout << "--FARMACIA MIRIAM------------" << endl;
            cout << "--Comprar-----------------[1]" << endl;
            cout << "--Consultar Stock---------[2]" << endl;
            cout << "--Ver Perfil--------------[3]" << endl;
            cout << "--Editar Perfil-----------[4]" << endl;
            cout << "--Historial de compras----[5]" << endl;
            cout << "--Salir-------------------[6]" << endl;
            getValue("Ingrese opcion[1-6]: ", &opt);
            switch (opt)
            {
            case 1:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 3:
                userController.getUsuario(key).listarDatos();
                break;
            case 4:
                system("cls");
                modifyPerfil(key);
                break;
            case 5:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 6:
                break;
            default:
                cout << "Ingrese una opción valida[1-5]" << endl;
                system("pause");
            }
        } while (opt != 6);
    }
    else if (userType == "Vendedor")
    {
        string type;
        do
        {
            system("cls");
            cout << "--FARMACIA MIRIAM------------" << endl;
            cout << "--Solicitudes de compra---[1]" << endl;
            cout << "--Editar Perfil-----------[2]" << endl;
            cout << "--Historial de ventas-----[3]" << endl;
            cout << "--Salir-------------------[4]" << endl;
            getValue("Ingrese opcion[1-4]: ", &opt);
            switch (opt)
            {
            case 1:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "Para modificar su perfil debe iniciar sesion como administrador" << endl;
                iniciarSesion(false, type);
                modifyPerfil(key);
                break;
            case 3:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 4:
                break;
            default:
                cout << "Ingrese una opción valida[1-4]" << endl;
                system("pause");
            }
        } while (opt != 4);
    }
    else
    {
        do
        {
            system("cls");
            cout << "--FARMACIA MIRIAM---------------" << endl;
            cout << "--Solicitudes de compra------[1]" << endl;
            cout << "--Editar Perfil--------------[2]" << endl;
            cout << "--Historial de ventas--------[3]" << endl;
            cout << "--Registrar nuevo Inventario-[4]" << endl;
            cout << "--Salir----------------------[5]" << endl;
            getValue("Ingrese opcion[1-5]: ", &opt);
            switch (opt)
            {
            case 1:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 2:
                system("cls");
                modifyPerfil(key);
                break;
            case 3:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "--AUN ESTAMOS TRABAJANDO EN ELLO--" << endl;
                system("pause");
                break;
            case 5:
                break;
            default:
                cout << "Ingrese una opción valida[1-5]" << endl;
                system("pause");
            }
        } while (opt != 5);
    }
}
void modifyPerfil(string key)
{
    int opt;
    do
    {
        system("cls");
        cout << "--EDITAR PERFIL------------" << endl;
        cout << "--Usuario---------------[1]" << endl;
        cout << "--Nombre----------------[2]" << endl;
        cout << "--Apellidos-------------[3]" << endl;
        cout << "--Contraseña-----------[4]" << endl;
        cout << "--Documento-------------[5]" << endl;
        cout << "--Salir-----------------[6]" << endl;
        getValue("Ingrese opcion[1-6]: ", &opt);
        switch (opt)
        {
        case 1:
            userController.getUsuario(key).modifyUsername();
            break;
        case 2:
            userController.getUsuario(key).modifyNombre();
            break;
        case 3:
            userController.getUsuario(key).modifyApellidos();
            break;
        case 4:
            userController.getUsuario(key).modifyContrasena();
            break;
        case 5:
            userController.getUsuario(key).modifyDocumento();
            break;
        case 6:
            break;
        default:
            cout << "Ingrese una opción valida[1-6]" << endl;
            system("pause");
            break;
        }
    } while (opt != 6);
    
}