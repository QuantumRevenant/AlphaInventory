#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../model/Usuario.cpp"
#include "../controller/controllers.h"
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
    // Usuario objUser(userController.getNewCodUsuario(),"admin",sha256("admin"),"admin","admin","DNI",10000000,"Administrador");
    // userController.add(objUser);
    // userController.archGrabarDatos();
    // Validar si hay administrador en el registro, sino:
    //  doRegistrarse(true)
    menuLogIn();
    esquinarTexto("...", 2, false, true, true);
    return 0;
}

void doRegistrarse(bool start = false)
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
        vector<string> options = {"VENDEDOR", "SUPERVISOR", "ADMINISTRADOR"};
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
        vector<string> inputs;
        do
        {
            cin.ignore();
            inputs.clear();
            options = {"Nombre de usuario", "Nombres", "Apellidos"};
            menuDatos(options, inputs, 0, 0, "__DATOS__");

            username = inputs[0].substr(0, inputs[0].find(' '));
            nombre = inputs[1];
            apellidos = inputs[2];

            if (userController.existeUsuario(username))
                menuError({"~USUARIO YA EXISTE, ESCOGE OTRO~"});
        } while (userController.existeUsuario(username));

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
            cin.ignore();
            inputs.clear();
            menuDatos({"Numero de documento"}, inputs, 0, 0, "_" + tipoDocumento + "_ -('Salir' para salir)");
            strInput = inputs[0].substr(0, inputs[0].find(' '));

            if (aMinuscula(strInput) == "salir")
                return;

            if ((int)strInput.size() != docSize)
            {
                options = {"~-Los documentos tipo " + tipoDocumento + " deben contener " + to_string(docSize) + " digitos-~", "~VUELVA A INGRESAR SU NUMERO DE DOCUMENTO~"};
                menuError(options, 1);
            }
            if (!esNumero(strInput))
                menuError({"~[[INTRODUCE UN VALOR NUMERICO]]~"});
        } while (!esNumero(strInput) || (int)strInput.size() != docSize);

        numDocumento = stoi(strInput);

        int sizePass;
        do
        {
            inputs.clear();
            menuDatos({"Contrasena", "Repetir Contrasena"}, inputs, 2, 1);
            contrasena = sha256(inputs[0]);
            contrasenaConfi = sha256(inputs[1]);
            sizePass = inputs[0].size();
            inputs.clear();

            if (sizePass < 8)
                menuError({"~-La contrasena debe tener minimo 8 caracteres-~", "~VUELVA A INGRESAR UNA CONTRASENA~"});
            else if (contrasena != contrasenaConfi)
                menuError({"~-Las contrasenas no son iguales-~", "~VUELVA A INGRESAR UNA CONTRASENA~"});

        } while (contrasena != contrasenaConfi || sizePass < 8);

        Usuario objUser(userController.getNewCodUsuario(), username, contrasena, nombre, apellidos, tipoDocumento, numDocumento, tipoUsuario);

        userController.add(objUser);
        objUser.listarDatos(); // BORRAR VERSION FINAL - SOLO DEBUG
        system("cls");
        userController.archGrabarDatos();
    }
}
void doModificarPerfil(int key)
{
    string temporal, temporal2;
    int opt, sizeTemporal;
    Usuario objUser = userController.getUsuario(key);
    vector<string> options;
    vector<string> inputs;
    do
    {
        inputs.clear();
        options = {"Usuario", "Nombres", "Apellidos", "Contrasena", "Documento", "Guardar Cambios"};
        opt = menu("EDITAR PERFIL", options);
        switch (opt)
        {
        case 1:
            menuDatos({"Nombre de usuario"}, inputs);
            temporal = inputs[0].substr(0, inputs[0].find(' '));
            if (userController.existeUsuario(temporal) && temporal != objUser.getUsername())
                menuError({"##[USUARIO YA EXISTE, ESCOGE OTRO NOMBRE]##"});
            if (menuConfirmar("Desea que\"" + temporal + "\"sea su nuevo nombre de usuario"))
                objUser.setUsername(temporal);
            break;
        case 2:
            menuDatos({"Nombre"}, inputs);
            temporal = inputs[0].substr(0, inputs[0].find(' '));
            if (menuConfirmar("Desea que\"" + temporal + "\"sea su nuevo nombre"))
                objUser.setNombre(temporal);
            break;
        case 3:
            menuDatos({"Apellidos"}, inputs);
            temporal = inputs[0].substr(0, inputs[0].find(' '));
            if (menuConfirmar("Desea que\"" + temporal + "\"sea sus nuevos apelidos"))
                objUser.setApellidos(temporal);
            break;
        case 4:
            do
            {
                inputs.clear();
                menuDatos({"Contrasena", "Repetir Contrasena"}, inputs, 2, 1, "-('Salir' para salir)-");
                if (aMinuscula(inputs[0]) != "salir" && aMinuscula(inputs[1]) != "salir")
                {
                    temporal = sha256(inputs[0]);
                    temporal2 = sha256(inputs[1]);
                    sizeTemporal = inputs[0].size();
                    inputs.clear();
                }
                else
                    break;

                if (sizeTemporal < 8)
                    menuError({"~-La contrasena debe tener minimo 8 caracteres-~", "~VUELVA A INGRESAR UNA CONTRASENA~"});
                else if (temporal != temporal2)
                    menuError({"~-Las contrasenas no son iguales-~", "~VUELVA A INGRESAR UNA CONTRASENA~"});

            } while (temporal != temporal2 || sizeTemporal < 8);
            objUser.setContrasena(temporal);
            temporal = temporal2 = "";
            sizeTemporal = 0;
            break;
        case 5:
            options = {"DNI", "CARNET EXTRANJERIA (CE)", "PASAPORTE", "RUC"}; // Carritos de compra, etc
            opt = menu("REGISTRO - TIPO DE USUARIO", options);

            switch (opt)
            {
            case 1:
                temporal = "DNI";
                sizeTemporal = 8;
                break;
            case 2:
                temporal = "CE";
                sizeTemporal = 12;
                break;
            case 3:
                temporal = "PASAPORTE";
                sizeTemporal = 12;
                break;
            case 4:
                temporal = "RUC";
                sizeTemporal = 11;
                break;
            case 0:
                temporal = "Cancelar";
                break;
            }

            if (temporal == "Cancelar")
                break;

            temporal2 = "0";
            do
            {
                cin.ignore();
                inputs.clear();
                menuDatos({"Numero de documento"}, inputs, 0, 0, "_" + temporal + "_ -('Salir' para salir)");
                temporal2 = inputs[0].substr(0, inputs[0].find(' '));

                if (aMinuscula(temporal2) == "salir")
                    return;

                if ((int)temporal2.size() != sizeTemporal)
                {
                    options = {"~-Los documentos tipo " + temporal + " deben contener " + to_string(sizeTemporal) + " digitos-~", "~VUELVA A INGRESAR SU NUMERO DE DOCUMENTO~"};
                    menuError(options, 1);
                }
                if (!esNumero(temporal2))
                    menuError({"~[[INTRODUCE UN VALOR NUMERICO]]~"});
            } while (!esNumero(temporal2) || (int)temporal2.size() != sizeTemporal);

            objUser.setDocumento(temporal);
            objUser.setNumDocumento(stoi(temporal2));
            break;
        case 6:
            if (menuConfirmar("Desea guardar los cambios", "Deberas reiniciar la sesion"))
            {
                userController.modify(objUser, key);
                userController.archGrabarDatos();
                progController.closeSesion();
            }
            else
                menuError({"Cancelando los cambios..."});
            break;
        case 0:
            if (menuConfirmar("Desea cancelar los cambios", "Se perderAn permanentemente"))
                menuError({"Cancelando los cambios..."});
            else
                opt = 7;
            break;
        }
    } while (opt != 6 && opt != 0);
}
bool doIniciarSesion(bool opt, string &type)
{
    cin.ignore();
    string username,
        contrasena;
    int contador = 0;
    bool resultado = false;
    do
    {
        vector<string> options = {"USERNAME", "CONTRASENA"};
        vector<string> inputs;
        menuDatos(options, inputs, 1, 1, "##INICIO DE SESIÓN## - ('Salir' para salir) ");
        if (aMinuscula(inputs[0]) == "salir" || aMinuscula(inputs[1]) == "salir")
            break;
        username=inputs[0];
        contrasena=inputs[1];
        resultado = userController.validarSesion(username, contrasena);
        if (resultado)
        {
            system("cls");
            dibujarCuadro();
            centrarTexto("Iniciando Sesión", 0, true, true, -3);
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                cout.flush();
                sleep(1);
            }
        }
        else
        {
            menuError({"Username y/o contraseña incorrectos."}, 0, "0f", "", true);
            contador++;
        }
    } while (!resultado && contador < 3);

    if (contador >= 3)
    {
        menuError({"Límite de intentos alcanzado, volviendo al menú principal..."}, 0, "0f", "", true);
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

        menuListado({"Sesion iniciada", "Bienvenido " + username});
        if (opt)
        {
            progController.openSesion(userController.getUsuario(username, contrasena).getCodUsuario(), isSupervisor, isAdm);
            menuMain();
            return true;
        }
        else
        {
            if (isAdm)
                type = "Administrador";
            else if (isSupervisor)
                type = "Supervisor";
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