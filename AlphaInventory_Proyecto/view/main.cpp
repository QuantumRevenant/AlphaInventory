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

int main(int argc, char *argv[])
{
    srand(time(NULL));
    /*
    Usuario objUser(userController.getNewCodUsuario(),"admin",sha256("admin"),"admin","admin","DNI",10000000,"Administrador");
    userController.add(objUser);
    userController.archGrabarDatos();
    Validar si hay administrador en el registro, sino:
     doRegistrarse(true)
    */
    if (userController.existeAdministrador())
    {
        // progController.openSesion(0, true, true);
        if (!progController.getActiveSesion())
            menuLogIn();
        else
            menuMain();
    }
    else
        doRegistrarse(true);

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
    vector<string> options;
    int sizeY = 3, e = 0;

    system("cls");
    if (!start)
    {
        options = {"VENDEDOR", "SUPERVISOR", "ADMINISTRADOR"};
        opt = menu("REGISTRO - TIPO DE USUARIO", options);
        switch (opt)
        {
        case 1:
            if (!progController.getActiveSesion() || !progController.getIsSupervisor())
            {
                menuListado({"~-NECESITAS INICIAR SESIÓN COMO SUPERVISOR O ADMINISTRADOR-~"}, 0, "", false);
                Sleep(1000);

                loged = doIniciarSesion(false, type);
                if (loged && (type == "Administrador" || type == "Supervisor"))
                    tipoUsuario = "Vendedor";
                else
                {
                    menuListado({"~-CANCELASTE EL REGISTRO-~"}, 0, "", true);
                    tipoUsuario = "Cancelar";
                    esquinarTexto("", 1, false, true, false);
                    system("pause");
                }
            }
            else
                tipoUsuario = "Vendedor";

            break;
        case 2:
            if (!progController.getActiveSesion() || !progController.getIsAdmin())
            {
                menuListado({"~-NECESITAS INICIAR SESIÓN COMO ADMINISTRADOR-~"}, 0, "", false);
                Sleep(1000);

                loged = doIniciarSesion(false, type);

                if (loged && type == "Administrador")
                    tipoUsuario = "Supervisor";
                else
                {
                    menuListado({"~-CANCELASTE EL REGISTRO-~"}, 0, "", true);
                    tipoUsuario = "Cancelar";
                    esquinarTexto("", 1, false, true, false);
                    system("pause");
                }
            }
            else
                tipoUsuario = "Supervisor";
            break;
        case 3:
            menuListado({"~-NECESITAS INICIAR SESIÓN / VOLVER A INICIAR COMO ADMINISTRADOR-~"}, 0, "", false);
            Sleep(1000);

            loged = doIniciarSesion(false, type);

            if (loged && type == "Administrador")
                tipoUsuario = "Administrador";
            else
            {
                menuListado({"~-CANCELASTE EL REGISTRO-~"}, 0, "", true);
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
    }
    else
    {
        menuError({"No tenemos un administrador registrado", "REGISTRA UNO NUEVO"});
        tipoUsuario = "Administrador";
    }

    vector<string> inputs;
    do
    {
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
    if (start)
    {
        if (!doIniciarSesion(true, type))
            menuLogIn();
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
        username = inputs[0];
        contrasena = inputs[1];
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

void doAddInventario()
{
}
void askInventario()
{
    int opt;
    vector<string> productos;
    for (int i = 0; i < productoController.getNewCodProducto(); i++)
        productos.push_back(productoController.get(i).getNombre() + "\t\t" + to_string(productoController.get(i).getStock()));
    if (productos.size() != 0)
    {
        do
        {
            opt = menu("PRODUCTOS", productos);
            if (opt != 0)
            {
                Producto temp;
                temp = productoController.get(opt - 1);
                vector<string> listado{to_string(temp.getCodProducto()), marcaController.get(temp.getCodMarca()).getNombreMarca(),
                                       temp.getNombre(), to_string(temp.getPrecioUnitario()), to_string(temp.getStock())};
                for (Componente x : temp.getVectorComponentes())
                    listado.push_back(x.getNombre() + "\t" + x.getCantidad());
                menuListado(listado, 0, aMayuscula(temp.getNombre()), true);
            }
        } while (opt != 0);
    }
    else
    {
        menuError({"No hay productos registrados, volviendo al menu inventario"});
    }
}
void changeDataInventario()
{
    int opt;
    int codigo;
    vector<string> inputs;
    string temporal;
    bool salida;
    vector<Componente> componentes;
    if (!progController.getActiveSesion() || !progController.getIsSupervisor())
    {
        menuError({"Necesitas iniciar sesión como Supervisor"});
        if (!doIniciarSesion(false, temporal))
            return;
        else if (temporal != "Supervisor" && temporal != "Admin")
            return;
    }

    do
    {
        salida = true;
        do
        {
            menuDatos({"Codigo Producto"}, inputs, 0, 0, "Cambiar Datos Producto -\"Salir\" para Salir");

            if (aMinuscula(inputs[0]) == "salir")
                break;
            if (!esNumero(inputs[0]))
            {
                menuError({"Introduce un valor numérico"});
                inputs[0] = "-1";
            }
            else if (stoi(inputs[0]) < 0 || stoi(inputs[0]) >= productoController.getNewCodProducto())
                menuError({"Codigo Fuera de Rango"});

        } while ((stoi(inputs[0]) < 0 || stoi(inputs[0]) >= productoController.getNewCodProducto()) && aMinuscula(inputs[0]) != "salir");

        if (aMinuscula(inputs[0]) == "salir")
            return;
        if (!menuConfirmar("El producto consultado es " + productoController.get(stoi(inputs[0])).getNombre()))
        {
            if (!menuConfirmar("Desea continuar con el proceso"))
                return;
            else
            {
                salida = false;
                cin.ignore();
            }
        }
    } while (!salida);

    codigo = stoi(inputs[0]);
    Producto prodTemporal = productoController.get(codigo);

    if (productoController.getNewCodProducto() != 0)
    {
        do
        {
            vector<string> options = {"Editar Nombre", "Modificar Marca", "Editar Precios", "Editar Componentes"};
            opt = menu("Selecciona que deseas modificar", options);
            inputs.clear();
            componentes.clear();
            switch (opt)
            {
            case 1:
                menuDatos({"Nuevo nombre de producto"}, inputs);
                temporal = inputs[0];
                if (menuConfirmar("Desea que \"" + temporal + "\" sea el nuevo nombre del producto"))
                    prodTemporal.setNombre(temporal);
                break;
            case 2:
                do
                {
                    menuDatos({"Nuevo código de marca"}, inputs);
                    temporal = inputs[0];
                    if (!esNumero(temporal))
                    {
                        menuError({"Introduce un valor numérico"});
                        temporal = "-1";
                    }
                    else if (stoi(temporal) < 0 || stoi(temporal) >= marcaController.getNewCodMarca())
                        menuError({"Codigo Fuera de Rango"});

                } while (stoi(temporal) < 0 || stoi(temporal) >= marcaController.getNewCodMarca() || temporal == "");

                if (menuConfirmar("Desea que\"" + marcaController.get(stoi(temporal)).getNombreMarca() + "\"sea la nueva marca"))
                    prodTemporal.setCodMarca(stoi(temporal));
                break;
            case 3:
                do
                {
                    menuDatos({"Nuevo precio Unitario"}, inputs);
                    temporal = inputs[0];
                    if (!esNumero(temporal))
                    {
                        menuError({"Introduce un valor numérico"});
                        temporal = "-1";
                    }
                } while (stod(temporal) < 0 || temporal == "");

                if (menuConfirmar("Desea que \"" + temporal + "\" sea el nuevo Precio"))
                    prodTemporal.setPrecioUnitario(stod(temporal));
                break;
            case 4:
                do
                {
                    int i = 0;
                    menuDatos({"Nombre del componente", "Cantidad del componente"}, inputs, 0, 0, "_COMPONENTE [" + to_string(i + 1) + "]_");
                    Componente temp(inputs[0], inputs[1]);
                    componentes.push_back(temp);
                    i++;
                } while (menuConfirmar("Desea agregar un nuevo componente"));

                if (menuConfirmar("Desea modificar los componentes"))
                    prodTemporal.setComponentes(componentes);
                break;
            case 0:
                productoController.modify(prodTemporal, codigo);
                productoController.saveFile();
                break;
            }
        } while (opt != 0);
    }
    else
    {
        menuError({"NO HAY PRODUCTOS REGISTRADOS"});
    }
}

void doAddProducto()
{
    int codMarca;
    int opt;
    int i;
    string temporal;
    vector<Componente> componentes;
    vector<string> inputs;
    vector<string> optionsM;
    if (!progController.getActiveSesion() || !progController.getIsSupervisor())
    {
        menuError({"Necesitas iniciar sesión como Supervisor"});
        if (!doIniciarSesion(false, temporal))
            return;
        else if (temporal != "Supervisor" && temporal != "Admin")
            return;
    }
    for (int i = 0; i < marcaController.getNewCodMarca(); i++)
        optionsM.push_back(marcaController.get(i).getNombreMarca());
    do
    {
        int codigo = productoController.getNewCodProducto();
        componentes.clear();
        i = 1;
        inputs.clear();
        cin.ignore();
        menuDatos({"Nombre del Producto"}, inputs, 0, 0, "_PRODUCTO [" + to_string(codigo) + "]_");
        string nombre = inputs[0];
        do
        {
            inputs.clear();
            cin.ignore();
            menuDatos({"Nombre del componente", "Cantidad del componente"}, inputs, 0, 0, "_COMPONENTE [" + to_string(i) + "]_");
            Componente temp(inputs[0], inputs[1]);
            componentes.push_back(temp);
            i++;
        } while (menuConfirmar("Desea agregar un nuevo componente"));
        if (marcaController.getNewCodMarca() != 0)
        {
            opt = menu("AGREGAR MARCAS", optionsM);
            if (opt != 0 && opt != -1)
            {
                codMarca = opt - 1;
                cin.ignore();
                do
                {
                    inputs.clear();
                    menuDatos({"Precio S/"}, inputs);
                    if (!esNumero(inputs[0]))
                        menuError({"Introduce un valor numérico"});
                } while (!esNumero(inputs[0]));
                double precio = stod(inputs[0]);
                Producto producto(productoController.getNewCodProducto(), codMarca, nombre, precio, 0, componentes);
                productoController.add(producto);
            }
        }
    } while (menuConfirmar("Desea agregar un nuevo producto"));
    productoController.saveFile();
}
void doAddMarca()
{
    int codigo;
    vector<string> inputs;
    string temporal;
    if (!progController.getActiveSesion() || !progController.getIsSupervisor())
    {
        menuError({"Necesitas iniciar sesión como Supervisor"});
        if (!doIniciarSesion(false, temporal))
            return;
        else if (temporal != "Supervisor" && temporal != "Admin")
            return;
    }
    do
    {
        codigo = marcaController.getNewCodMarca();
        inputs.clear();
        cin.ignore();
        menuDatos({"Nombre de la marca"}, inputs, 0, 0, "_MARCA [" + to_string(codigo) + "]_");
        Marca marca(codigo, inputs[0]);
        marcaController.add(marca);
    } while (menuConfirmar("Desea agregar una nueva marca"));
    marcaController.saveFile();
}
