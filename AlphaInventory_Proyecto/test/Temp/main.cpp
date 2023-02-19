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

void menuPrincipal();
void menuUsuario();
void menuTest(string, string);
bool iniciarSesion(bool, string &);
void registrarse(bool);
void modifyPerfil(string);

int main(/*int argc, char *argv[]*/)
{
    srand(time(NULL));
    userController.archRecuperarDatos();
    registrarse(true);
    // Usuario temp("admin", temp.encriptar("12345678"), "Admin", "Admin", "DNI", 12345678, "Administrador"); //
    // userController.add(temp);                                                                              //
    menuPrincipal();                                                                                       //
    return 0;
}
void menuPrincipal()
{
    cout << "Menu Principal" << endl;
    sleep(1);
    cout << "Menu Usuario" << endl;
    sleep(1);
    if (!confirmar("cerrar el programa"))
        menuUsuario();
    else
        cout << "#####Gracias por usar nuestro servicio#####" << endl;
}
void menuUsuario()
{
    string type,
        username;
    int opt;
    int i;
    do
    {
        system("cls");
        i = 1;
        cout << "--FARMACIA MIRIAM------------" << endl;
        if (!progController.getActiveSesion())
        {
            cout << "--Iniciar Sesion----------[" << i << "]" << endl;
            cout << "--Registrarse-------------[" << i + 1 << "]" << endl;
            cout << "--Continuar como Invitado-[" << i + 2 << "]" << endl;
            i += 3;
        }
        else
        {
            cout << "--Leer Mis Datos(DEMO)----[" << i << "]" << endl;
            cout << "--Modificar Datos---------[" << i + 1 << "]" << endl;
            cout << "--Cerrar Sesión-----------[" << i + 2 << "]" << endl;
            i += 3;
        }
        cout << "--Salir del Menú----------[" << i << "]" << endl;

        getValue("Ingrese opcion[1-" + to_string(i) + "]: ", &opt);

        if (!progController.getActiveSesion())
        {
            switch (opt)
            {
            case 1:
                system("cls");
                iniciarSesion(true, type);
                menuPrincipal();
                break;
            case 2:
                system("cls");
                registrarse(false);
                break;
            case 3:
                cout << "Ingresó como Invitado [FUNCIÓN AUN NO IMPLEMENTADA]" << endl;
                menuPrincipal();
                system("pause");
                // menuUsuario("Invitado", NULL);
                break;
            case 4: // cambiar el valor de acuerdo a i
                menuPrincipal();
                system("pause");
                break;
            default:
                cout << "Ingrese una opción valida[1-" << i << +"]" << endl;
                system("pause");
            }
        }
        else
        {
            switch (opt)
            {
            case 1:
                system("cls");
                userController.getUsuario(progController.getSesionKey()).listarDatos();
                menuUsuario();
                break;
            case 2:
                system("cls");
                modifyPerfil(progController.getSesionKey());
                userController.archGrabarDatos();
                menuPrincipal();
                break;
            case 3:
                // Cerrar Sesion
                system("cls");
                cout << "Cerrando Sesión"; // Agregar el inicio de sesión
                for (int i = 0; i < 3; i++)
                {
                    cout << ".";
                    cout.flush();
                    sleep(1);
                }
                cout << endl;
                username = userController.getUsuario(progController.getSesionKey()).getUsername();
                progController.closeSesion();
                cout << "Sesion cerrada" << endl;
                sleep(1);
                cout << "Hasta pronto, " << username << endl;
                sleep(1);
                system("pause");
                menuPrincipal();
                // menuUsuario("Invitado", NULL);
                break;
            case 4: // cambiar el valor de acuerdo a i
                menuPrincipal();
                system("pause");
                break;
            default:
                cout << "Ingrese una opción valida[1-" << i << +"]" << endl;
                system("pause");
            }
        }
    } while (opt < 1 || i < opt);
}
void menuTest(string userType, string key)
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
                registrarse(false);
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
    } while (!resultado && contador < 3);

    if (contador >= 3)
    {
        cout << "Límite de intentos alcanzado, volviendo al menú principal..." << endl;
        system("pause");
        return false;
    }

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
            progController.openSesion(userController.getUsuario(username, contrasena).getCodUsuario(), isSell, isAdm);
            cout << "Sesion iniciada" << endl;
            sleep(1);
            cout << "Bienvenido " << username << endl;
            sleep(1);
            cout << "Ingresó como Usuario [FUNCIÓN AUN NO IMPLEMENTADA]" << endl;
            system("pause");
            // menuUsuario(userController.getUsuario(username, contrasena).getTipoUsuario(), userController.getUsuario(username, contrasena).getCodUsuario());
            return true;
        }
        else
        {
            if (isAdm)
                type = "Administrador";
            cout << "Sesion iniciada" << endl;
            sleep(1);
            cout << "Bienvenido " << username << endl;
            sleep(1);
            system("pause");
            return true;
        }
    }
    return NULL;
}
void registrarse(bool start)
{
    string type;
    string username;
    string nombre;
    string apellidos;
    string strInput;
    long int numDocumento;
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
                admLoged = iniciarSesion(false, type);
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
        iniciarSesion(true, type);
        menuPrincipal();
    }
}
void modifyPerfil(string key)
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