#include <iostream>
#include <random>
#include <ctime>
#include "../model/Usuario.cpp"
#include "../controller/usuarioController.h"
#include "../controller/programController.h"
using namespace std;

usuarioController userController;
programController progController;

void getValue(string, string *);
void getValue(string, int *);
void menuLogin();
bool iniciarSesion(bool);
void registrarse();

int main(int argc, char *argv[])
{
    srand(time(NULL));
    menuLogin();
    return 0;
}

void getValue(string mensaje, string *dato)
{
    cout << mensaje;
    cin >> *dato;
}
void getValue(string mensaje, int *dato)
{
    cout << mensaje;
    cin >> *dato;
}
void menuLogin()
{
    int opt;
    do
    {
        system("cls");
        cout << "--FARMACIA MIRIAM-----------" << endl;
        cout << "--Iniciar Sesion---------[1]" << endl;
        cout << "--Registrarse------------[2]" << endl;
        cout << "--Salir------------------[3]" << endl;
        getValue("Ingrese opcion[1-3]: ", &opt);
        switch (opt)
        {
        case 1:
            system("cls");
            iniciarSesion(true);
            break;
        case 2:
            system("cls");
            registrarse();
            break;
        case 3:
            cout << "#####Gracias por usar nuestro servicio#####";
            break;
        default:
            cout << "Ingrese una opción valida[1-3]" << endl;
            system("pause");
        }
    } while (opt != 3);
}
bool iniciarSesion(bool opt)
{
    return opt;
    // el bool tenia pensado que podriamos usarlo para detener la funcion a la mitad, false: solo inicia sesion, true: inicia sesion y despliega un menu de opciones(depende del tipo de usuario)
}
void registrarse()
{
    // Usuario objUser;
    string username;
    string nombre;
    string apellidos;
    int numDocumento;
    string tipoUsuario;
    string tipoDocumento;
    string contrasena;
    string contrasenaConfi;
    int opt;

    do
    {
        system("cls");
        cout << "--TIPO DE USUARIO-----------" << endl;
        cout << "--CLIENTE----------------[1]" << endl;
        cout << "--VENDEDOR---------------[2]" << endl;
        cout << "--ADMINISTRADOR----------[3]" << endl;
        cout << "--CANCELAR---------------[4]" << endl;
        getValue("Ingrese opcion[1-3]: ", &opt);
        if (opt == 2 || opt == 3)
        {
            cout << "Para crear un usuario de vendedor o administrador, debe iniciar sesion como administrador" << endl;
            iniciarSesion(false);
            break;
        }
        switch (opt)
        {
        case 1:
            tipoUsuario="Cliente";
            break;
        case 2:
            tipoUsuario="Vendedor";
            break;
        case 3:
            tipoUsuario="Administrador";
            break;
        case 4:
            cout<<"Cancelando...";
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
        }
    } while (opt != 1 && opt != 2 && opt != 3);
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
        cout << "--CE---------------------[2]" << endl;
        cout << "--Pasaporte--------------[3]" << endl;
        cout << "--RUC--------------------[4]" << endl;
        getValue("Ingrese opcion[1-4]: ", &opt);
        switch (opt)
        {
        case 1:
            tipoDocumento="DNI";
            break;
        case 2:
            tipoDocumento="CE";
            break;
        case 3:
            tipoDocumento="Pasaporte";
            break;
        case 4:
            tipoDocumento="RUC";
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
        }
    } while (opt != 1 && opt != 2 && opt != 3 && opt != 4);
    getValue("Numero de documento: ", &numDocumento);
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

    Usuario objUser(username,contrasena,nombre,apellidos,tipoDocumento,numDocumento,tipoUsuario);

    userController.add(objUser);
    iniciarSesion(true);
}