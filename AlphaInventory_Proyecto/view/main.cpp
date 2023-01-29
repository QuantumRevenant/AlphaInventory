#include <iostream>
#include <random>
#include <ctime>
#include "../model/Usuario.cpp"
#include "../controller/usuarioController.h"
#include "../controller/programController.h"
#include "../model/FuncionesGenerales.h"
using namespace std;

usuarioController userController;
programController progController;

void getValue(string, string *);
void getValue(string, int *);
void menuLogin();
bool iniciarSesion(bool, string &);
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
    string type;
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
            iniciarSesion(true, type);
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
        cout << "CONTRASEÑA: ";
        cin >> contrasena;
        resultado = userController.validarSesion(username, contrasena);
        if (resultado)
            cout << "Iniciando Sesión..." << endl; // Agregar el inicio de sesión
        else
        {
            cout << "Username y contraseña incorrectos y/o no registrados en nuestra base de datos." << endl;
            contador++;
        }
    } while (!resultado || contador >= 3 || aMinuscula(username) == "salir" || aMinuscula(contrasena) == "salir");

    if (resultado && contador < 3 && aMinuscula(username) != "salir" && aMinuscula(contrasena) != "salir")
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
            cout<<"sesion iniciada"<<endl;
            system("pause");
            return true;
        }
        else
        {
            type = tempUser.getTipoUsuario();
            return true;
        }
    }
    return NULL;
    // el bool tenia pensado que podriamos usarlo para detener la funcion a la mitad, false: solo inicia sesion, true: inicia sesion y despliega un menu de opciones(depende del tipo de usuario)
}
void registrarse()
{
    // Usuario objUser;
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
    int opt = 1;
    int docSize;

    do
    {
        // system("cls");
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
            cout << "Cancelando...";
            break;
        default:
            cout << "Ingrese una opción valida[1-4]" << endl;
            system("pause");
        }
    } while (opt <= 0 && opt >= 5);
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
    system("cls");
    cout<<username<<endl<<contrasena<<endl<<contrasenaConfi<<endl<<nombre<<endl<<apellidos<<endl<<tipoDocumento<<endl<<numDocumento<<endl<<tipoUsuario<<endl;
    system("pause");
    iniciarSesion(true, type);
}