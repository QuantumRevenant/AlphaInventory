#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../model/Usuario.cpp"
#include "../model/models.h"
#include "../controller/controllers.h"
#include "OptionMenus.h"

using namespace std;

int main(int argc, char *argv[])
{
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    srand(time(NULL));
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

void showKardex(int cod)
{
    bool menorIgualMax = false;

    int x, y;
    int iterador = 0;
    int movesQuant = 0;
    int intAcum = 0;
    system("cls");
    dibujarCuadro();
    esquinarTexto(" >Producto: " + productoController.get(cod).getNombre(), 1, true);
    esquinarTexto(">Precio: S/." + to_string(productoController.get(cod).getPrecioUnitario()).substr(0, to_string(productoController.get(cod).getPrecioUnitario()).size() - 4) + "  ", 1, true, false);

    vector<kardex> movimientos = kardexController.getMovimientosProducto(cod);
    vector<kardex> movimientosMostrar;
    string temporal;
    if (movimientos.size() <= 10)
    {
        movimientosMostrar = movimientos;
        menorIgualMax = true;
    }
    else
    {
        kardex obj = movimientos[0];
        movimientosMostrar.push_back(obj);
        for (int i = 9; i > 0; i--)
        {

            int cantidad = movimientos.size();
            cantidad -= i;
            movimientosMostrar.push_back(movimientos[cantidad]);
        }
        menorIgualMax = false;
    }

    vector<string> NumMovimientos, Fechas, Comprobantes, Entradas, Salidas, Acumulados;
    if (menorIgualMax)
    {
        for (int i = 0; i < movimientosMostrar.size(); i++)
        {
            NumMovimientos.push_back(to_string(movimientosMostrar.size() - i));
            Fechas.push_back(movimientosMostrar[i].getFechaDeEmision());

            if (movimientosMostrar[i].getComprobante().size() > 20)
                temporal = movimientosMostrar[i].getComprobante().substr(0, 17) + "...";
            else
                temporal = movimientosMostrar[i].getComprobante();
            Comprobantes.push_back(temporal);

            if (movimientosMostrar[i].getIsSalida())
            {
                Entradas.push_back("");
                Salidas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                intAcum -= movimientosMostrar[i].getCantidad();
            }
            else
            {
                Entradas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                Salidas.push_back("");
                intAcum += movimientosMostrar[i].getCantidad();
            }
            Acumulados.push_back(to_string(intAcum));
            movesQuant = i + 1;
        }
    }
    else
    {
        NumMovimientos.push_back(to_string(movimientosMostrar.size()));
        Fechas.push_back(movimientosMostrar[0].getFechaDeEmision());
        if (movimientosMostrar[0].getComprobante().size() > 20)
            temporal = movimientosMostrar[0].getComprobante().substr(0, 17) + "...";
        else
            temporal = movimientosMostrar[0].getComprobante();
        Comprobantes.push_back(temporal);

        if (movimientosMostrar[0].getIsSalida())
        {
            Entradas.push_back("");
            Salidas.push_back(to_string(movimientosMostrar[0].getCantidad()));
            intAcum -= movimientosMostrar[0].getCantidad();
        }
        else
        {
            Entradas.push_back(to_string(movimientosMostrar[0].getCantidad()));
            Salidas.push_back("");
            intAcum += movimientosMostrar[0].getCantidad();
        }
        Acumulados.push_back(to_string(intAcum));

        NumMovimientos.push_back("...");
        Fechas.push_back("...");
        Comprobantes.push_back("...");
        Entradas.push_back("...");
        Salidas.push_back("...");
        Acumulados.push_back("...");

        for (int i = 1; i < movimientosMostrar.size(); i++)
        {
            NumMovimientos.push_back(to_string(movimientosMostrar.size() - i - 1));
            Fechas.push_back(movimientosMostrar[i].getFechaDeEmision());

            if (movimientosMostrar[i].getComprobante().size() > 20)
                temporal = movimientosMostrar[i].getComprobante().substr(0, 17) + "...";
            else
                temporal = movimientosMostrar[i].getComprobante();
            Comprobantes.push_back(temporal);

            if (movimientosMostrar[i].getIsSalida())
            {
                Entradas.push_back("");
                Salidas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                intAcum -= movimientosMostrar[i].getCantidad();
            }
            else
            {
                Entradas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                Salidas.push_back("");
                intAcum += movimientosMostrar[i].getCantidad();
            }
            Acumulados.push_back(to_string(intAcum));
            movesQuant = i + 1;
        }
    }

    for (int j = 1; j < XSIZECMD; j++)
    {
        for (int k = 1; k <= YSIZECMD; k++)
        {
            if (((j > 95 && j < 117) && (k == YSIZECMD - 3)) || ((j > 1 && j < XSIZECMD - 1) && (k == 7)))
                cout << "-";
            gotoxy(j, k);
            if ((j == 13 || j == 26 || j == 49 || j == 72 || j == 95) && ((k < YSIZECMD - 2 && k > 4)))
                cout << "|";
        }
    }

    y = 7;

    gotoxy(4, y - 2);
    cout << "Num Mov:";

    gotoxy(15, y - 2);
    cout << "Fechas:";

    gotoxy(28, y - 2);
    cout << "Comprobante:";

    gotoxy(51, y - 2);
    cout << "ENTRADAS:";

    gotoxy(74, y - 2);
    cout << "SALIDAS:";

    gotoxy(97, y - 2);
    cout << "ACUMULADOS:";
    for (int k = 1; k <= YSIZECMD; k++)
    {

        for (int j = 1; j < XSIZECMD; j++)
        {
            gotoxy(j, k);
            if ((k == y) && y < YSIZECMD - 4)
            {
                if (j == 5)
                    cout << NumMovimientos[iterador];

                if (j == 15)
                {
                    cout << Fechas[iterador];
                }

                if (j == 28)
                    cout << Comprobantes[iterador];

                if (j == 51)
                    cout << Entradas[iterador];

                if (j == 74)
                    cout << Salidas[iterador];

                if (j == 97)
                {
                    cout << Acumulados[iterador];
                    iterador++;
                    y += 2;
                }
            }
            if (iterador == movesQuant)
                break;
        }
        if (iterador == movesQuant)
            break;
    }

    gotoxy(87, YSIZECMD - 3);
    cout << "TOTAL: ";
    gotoxy(97, YSIZECMD - 3);
    cout << Acumulados.back();

    esquinarTexto("", 1);
    system("pause");
}

void doRegistrarse(bool start = false)
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
                menuListado({"~-NECESITAS INICIAR SESI�N COMO SUPERVISOR O ADMINISTRADOR-~"}, 0, "", false);
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
                menuListado({"~-NECESITAS INICIAR SESI�N COMO ADMINISTRADOR-~"}, 0, "", false);
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
            menuListado({"~-NECESITAS INICIAR SESI�N / VOLVER A INICIAR COMO ADMINISTRADOR-~"}, 0, "", false);
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

    numDocumento = stoll(strInput);

    int sizePass;
    do
    {
        ;
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
            temporal = inputs[0];
            if (menuConfirmar("Desea que\"" + temporal + "\"sea su nuevo nombre"))
                objUser.setNombre(temporal);
            break;
        case 3:
            menuDatos({"Apellidos"}, inputs);
            temporal = inputs[0];
            if (menuConfirmar("Desea que\"" + temporal + "\"sea sus nuevos apellidos"))
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
            objUser.setNumDocumento(stoll(temporal2));
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
        menuDatos(options, inputs, 1, 1, "##INICIO DE SESI�N## - ('Salir' para salir) ");
        if (aMinuscula(inputs[0]) == "salir" || aMinuscula(inputs[1]) == "salir")
            break;
        username = inputs[0];
        contrasena = inputs[1];
        resultado = userController.validarSesion(username, contrasena);
        if (resultado)
        {
            system("cls");
            dibujarCuadro();
            centrarTexto("Iniciando Sesi�n", 0, true, true, -3);
            for (int i = 0; i < 3; i++)
            {
                cout << ".";
                cout.flush();
                sleep(1);
            }
        }
        else
        {
            menuError({"Username y/o contrase�a incorrectos."}, 0, "0f", "", true);
            contador++;
        }
    } while (!resultado && contador < 3);

    if (contador >= 3)
    {
        menuError({"L�mite de intentos alcanzado, volviendo al men� principal..."}, 0, "0f", "", true);
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

void doCompra()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;

    long long int proveedorRUC;
    bool usuarioRegistrado;
    int codProducto;
    string nomProducto;
    double precioUnitario;
    int cantProducto;
    double montoProducto;
    double montoTotal;
    string comprobante;
    string fecha;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(false);

    bool enCarrito = false;
    vector<CompraD> carrito;
    vector<kardex> kardexCarrito;
    Compra tempCompra;
    CompraD tempCompraD;
    kardex tempKardex;

    menuListado({"Inicializando Compra..."}, 0, "Compra #" + to_string(compraController.size() + 1), false);
    Sleep(1000);

    cout << "here" << endl;
    // FECHA
    if (menuConfirmar("Desea usar la fecha de hoy para registrar la compra"))
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    else
    {
        do
        {
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        fecha = inputs[0];
    }

    inputs.clear();
    // RUC
    string nombreProveedor;
    vector<string> listaProveedores;
    for (int i = 0; i < proveedorController.size(); i++)
        listaProveedores.push_back(proveedorController.get(i).getNombre());
    do
    {
        opt = menu("_Seleccion de proveedor_", {"Por Nombre", "Por RUC"});
        switch (opt)
        {
        case 1:
            nombreProveedor = menuBusqueda(listaProveedores, 0, "_Proveedor_");
            if (nombreProveedor == "salir")
                opt = -1;
            else
            {
                for (int i = 0; i < proveedorController.size(); i++)
                    if (proveedorController.get(i).getNombre() == nombreProveedor)
                    {
                        proveedorRUC = proveedorController.get(i).getDocumento();
                        break;
                    }
            }
            break;
        case 2:
            do
            {
                usuarioRegistrado = true;
                do
                {
                    inputs.clear();
                    menuDatos({"RUC"}, inputs, 0, 0, "Datos del Proveedor Compra #" + to_string(compraController.size() + 1)); // Proveedores
                    if (!esNumero(inputs[0]))
                        menuError({"Introduzca un valor numerico"});
                    if (inputs[0].size() != 11)
                        menuError({"El RUC tiene 11 D�gitos"});
                } while (!esNumero(inputs[0]) || inputs[0].size() != 11 || aMinuscula(inputs[0]) == "salir");

                if (aMinuscula(inputs[0]) == "salir")
                    break;

                proveedorRUC = stoll(inputs[0]);
                inputs.clear();

                if (proveedorController.getPosRUC(proveedorRUC) == -1)
                {
                    menuError({"RUC NO REGISTRADO"});
                    if (menuConfirmar("Desea registrar un nuevo Proveedor"))
                    {
                        if (doRegistrarTercero(false, proveedorRUC) == -1)
                            return;
                        usuarioRegistrado = false;
                        menuListado({"Vuelve a buscar el nombre del usuario"});
                    }
                    else
                        return;
                }
            } while (!usuarioRegistrado);
            break;
        default:
            break;
        }
    } while (opt != 1 && opt != 2 && opt != 0);
    if (opt == 0)
        return;

    // COMPROBANTE COMPRA PRODUCTO
    do
    {
        ;
        inputs.clear();
        menuDatos({"Comprobante de Compra"}, inputs, 0, 0, "Datos del Comprobante Compra #" + to_string(compraController.size() + 1)); // Producto
        if (aMinuscula(inputs[0]) == "salir")
            return;
    } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));

    comprobante = inputs[0];
    inputs.clear();

    string nombreProducto;
    vector<string> listaProductos;
    for (int i = 0; i < productoController.size(); i++)
        listaProductos.push_back(productoController.get(i).getNombre());

    do
    {
        opt = menu("_Carrito de Compra_ #" + to_string(compraController.size() + 1), {"Agregar producto", "Eliminar Producto", "Mirar Carrito de Compra", "Finalizar Compra"});
        switch (opt)
        {
        case 1:
            // CODIGO PRODUCTO
            nombreProducto = menuBusqueda(listaProductos, 0, "_Busqueda Producto_");
            if (nombreProducto == "salir")
                break;

            for (int i = 0; i < productoController.size(); i++)
                if (productoController.get(i).getNombre() == nombreProducto)
                    codProducto = productoController.get(i).getCodProducto();

            // CANTIDAD PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            cantProducto = stoi(inputs[0]);
            inputs.clear();

            // PRECIO COMPRA PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Costo Unitario"}, inputs, 0, 0, "Producto Compra #" + to_string(compraController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            montoProducto = stoi(inputs[0]);
            inputs.clear();

            enCarrito = false;
            for (int i = 0; i < carrito.size(); i++)
                if (carrito[i].getCodProducto() == codProducto)
                {
                    carrito[i].setCantidad(carrito[i].getCantidad() + cantProducto);
                    carrito[i].setMonto(carrito[i].getCantidad() * carrito[i].getPrecio());
                    enCarrito = true;
                }
            if (!enCarrito)
            {
                tempCompraD.setCodCompra(compraController.size());
                tempCompraD.setCodProducto(codProducto);
                tempCompraD.setCantidad(cantProducto);
                tempCompraD.setPrecio(montoProducto);
                tempCompraD.setMonto(montoProducto * cantProducto);
                carrito.push_back(tempCompraD);
            }
            
            break;
        case 2:
            do
            {
                listado.clear();
                for (CompraD x : carrito)
                    listado.push_back(productoController.get(x.getCodProducto()).getNombre());
                opt = menu("Suprimir Productos Compra #" + to_string(compraController.size() + 1), listado);
                if (opt != 0 && opt != -1)
                {
                    carrito.erase(carrito.begin() + opt - 1);
                    listado.erase(listado.begin() + opt - 1);
                }
            } while (opt != 0);
            opt = 2;
            break;

        case 3:
            listado.clear();
            for (CompraD x : carrito)
            {
                nombreProducto = productoController.get(x.getCodProducto()).getNombre();
                precioUnitario = x.getPrecio();
                cantProducto = x.getCantidad();
                montoProducto = x.getMonto();
                listado.push_back(nombreProducto + "\tS/" + to_string(precioUnitario) + "\t" + to_string(cantProducto) + "u\tS/" + to_string(montoProducto));
            }
            menuListado(listado, 0, "Compra #" + to_string(compraController.size() + 1));
            break;

        case 4:
            listado.clear();
            for (CompraD x : carrito)
            {
                nombreProducto = productoController.get(x.getCodProducto()).getNombre();
                precioUnitario = x.getPrecio();
                cantProducto = x.getCantidad();
                montoProducto = x.getMonto();
                listado.push_back(nombreProducto + "\tS/" + to_string(precioUnitario) + "\t" + to_string(cantProducto) + "u\tS/" + to_string(montoProducto));
            }
            menuListado(listado, 0, "Compra #" + to_string(compraController.size() + 1));
            if (menuConfirmar("Desea agregar una observacion a esta compra"))
            {
                ;
                menuDatos({""}, inputs, 0, 0, "Observacion Compra #" + to_string(compraController.size() + 1));
                observacion = inputs[0];
            }
            montoTotal = 0;
            for (CompraD x : carrito)
            {
                tempKardex.setCantidad(x.getCantidad());
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setCodProducto(x.getCodProducto());
                tempKardex.setCodProceso(createCode("CP", compraController.size(), 5));
                tempKardex.setComprobante(comprobante);
                tempKardex.setFechaDeEmision(fecha);
                tempKardex.setIsSalida(false);
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setMotivo("~~Compra " + to_string(cantComprobantes) + "~~");
                tempKardex.setObservacion(observacion);
                kardexController.add(tempKardex);
                compraDController.add(x);
                kardexController.saveFile();
                compraDController.saveFile();
                montoTotal += (x.getPrecio() * x.getCantidad());
            }
            tempCompra.setCodCompra(compraController.size());
            tempCompra.setCodProveedor(proveedorController.getPosRUC(proveedorRUC));
            tempCompra.setCodUsuario(progController.getSesionKey());
            tempCompra.setFecha(fecha);
            tempCompra.setMonto(montoTotal);
            tempCompra.setEstado(true);
            compraController.add(tempCompra);
            compraController.saveFile();
            opt = 0;
            break;
        case 0:
            if (!menuConfirmar("Seguro que desea cancelar la compra"))
                opt = -1;
            break;
        default:
            break;
        }
    } while (opt != 0);
}

void doVenta()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;
    vector<string> options;
    string tipoDocumento;
    bool usuarioRegistrado;

    long long int clienteDNI;
    int codProducto;
    string nomProducto;
    double precioUnitario;
    int cantProducto;
    double montoProducto;
    double montoTotal;
    string comprobante;
    string fecha;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(true);

    bool enCarrito = false;
    vector<VentaD> carrito;
    vector<kardex> kardexCarrito;
    Venta tempVenta;
    VentaD tempVentaD;
    kardex tempKardex;

    menuListado({"Inicializando Venta..."}, 0, "Venta #" + to_string(ventaController.size() + 1), false);
    Sleep(1000);

    cout << "here" << endl;
    // FECHA
    if (menuConfirmar("Desea usar la fecha de hoy para registrar la Venta"))
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    else
    {
        do
        {
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        fecha = inputs[0];
    }

    inputs.clear();
    // DNI
    string nombreCliente;
    vector<string> listaClientes;
    for (int i = 0; i < clienteController.size(); i++)
        listaClientes.push_back(clienteController.get(i).getNombre());
    do
    {
        opt = menu("_Seleccion de cliente_", {"Por Nombre", "Por Documento"});
        switch (opt)
        {
        case 1:
            nombreCliente = menuBusqueda(listaClientes, 0, "_Cliente_");
            if (nombreCliente == "salir")
                opt = -1;
            else
            {
                for (int i = 0; i < clienteController.size(); i++)
                    if (clienteController.get(i).getNombre() == nombreCliente)
                    {
                        cout << clienteController.get(i).getDocumento() << endl;
                        clienteDNI = clienteController.get(i).getDocumento();
                        tipoDocumento = clienteController.get(i).getTipoDocumento();
                        break;
                    }
            }
            break;
        case 2:
            do
            {
                usuarioRegistrado = true;
                options = {"DNI", "CARNET EXTRANJERIA (CE)", "PASAPORTE", "RUC"}; // Carritos de compra, etc
                opt = menu("REGISTRO - TIPO DE USUARIO", options);

                switch (opt)
                {
                case 1:
                    tipoDocumento = "DNI";
                    break;
                case 2:
                    tipoDocumento = "CE";
                    break;
                case 3:
                    tipoDocumento = "PASAPORTE";
                    break;
                case 4:
                    tipoDocumento = "RUC";
                    break;
                case 0:
                    tipoDocumento = "Cancelar";
                    break;
                }
                if (tipoDocumento == "Cancelar")
                    return;
                do
                {
                    inputs.clear();
                    menuDatos({"Documento"}, inputs, 0, 0, "Datos del Cliente Venta #" + to_string(ventaController.size() + 1)); // Clientes
                    if (!esNumero(inputs[0]))
                        menuError({"Introduzca un valor numerico"});
                    // if (inputs[0].size() != 8)
                    //     menuError({"El DNI tiene 8 D�gitos"});
                } while (!esNumero(inputs[0]) /*|| inputs[0].size() != 8*/ || aMinuscula(inputs[0]) == "salir");

                if (aMinuscula(inputs[0]) == "salir")
                    break;

                clienteDNI = stoll(inputs[0]);

                inputs.clear();

                if (clienteController.getPosDoc(clienteDNI, tipoDocumento) == -1)
                {
                    menuError({aMayuscula(tipoDocumento) + " NO REGISTRADO"});
                    if (menuConfirmar("Desea registrar un nuevo Cliente"))
                    {
                        if (doRegistrarTercero(true, clienteDNI) == -1)
                            return;
                        usuarioRegistrado = false;
                        menuListado({"Vuelve a buscar el nombre del usuario"});
                    }
                    else
                        return;
                }
            } while (!usuarioRegistrado);
            break;
        default:
            break;
        }
    } while (opt != 1 && opt != 2 && opt != 0);
    if (opt == 0)
        return;

    // COMPROBANTE VENTA PRODUCTO

    inputs.clear();

    if (tipoDocumento == "RUC")
    {
        comprobante = createCode("FV", kardexController.getCantidadComprobanteVenta(false));
    }
    else
    {
        comprobante = createCode("BV", kardexController.getCantidadComprobanteVenta(true));
    }

    string nombreProducto;
    vector<string> listaProductos;
    for (int i = 0; i < productoController.size(); i++)
        listaProductos.push_back(productoController.get(i).getNombre());
    do
    {
        opt = menu("_Carrito de " + clienteController.get(clienteController.getPosDoc(clienteDNI, tipoDocumento)).getNombre() + " de Venta_ #" + to_string(ventaController.size() + 1), {"Agregar producto", "Eliminar Producto", "Mirar Carrito de Compra", "Finalizar Compra"});
        switch (opt)
        {
        case 1:
            // CODIGO PRODUCTO
            nombreProducto = menuBusqueda(listaProductos, 0, "_Busqueda Producto_");
            if (nombreProducto == "salir")
                break;

            for (int i = 0; i < productoController.size(); i++)
                if (productoController.get(i).getNombre() == nombreProducto)
                    codProducto = productoController.get(i).getCodProducto();

            // CANTIDAD PRODUCTO
            do
            {
                inputs.clear();
                menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Venta #" + to_string(ventaController.size() + 1)); // Producto
                if (!esNumero(inputs[0]))
                    menuError({"Introduzca un valor numerico"});
                if (inputs[0].size() < 0)
                    menuError({"Cantidad Invalida"});
            } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

            if (aMinuscula(inputs[0]) == "salir")
                return;

            cantProducto = stoi(inputs[0]);
            inputs.clear();

            enCarrito = false;
            for (int i = 0; i < carrito.size(); i++)
                if (carrito[i].getCodProducto() == codProducto)
                {
                    carrito[i].setCantidad(carrito[i].getCantidad() + cantProducto);
                    carrito[i].setMonto(carrito[i].getCantidad() * carrito[i].getPrecio());
                    enCarrito = true;
                }
            
            if (!enCarrito)
            {
                tempVentaD.setCodVenta(ventaController.size());
                tempVentaD.setCodProducto(codProducto);
                tempVentaD.setCantidad(cantProducto);
                tempVentaD.setPrecio(productoController.get(codProducto).getPrecioUnitario());
                tempVentaD.setMonto(productoController.get(codProducto).getPrecioUnitario() * cantProducto);
                carrito.push_back(tempVentaD);
            }
            break;
        case 2:
            do
            {
                listado.clear();
                for (VentaD x : carrito)
                    listado.push_back(productoController.get(x.getCodProducto()).getNombre());
                opt = menu("Suprimir Productos Venta #" + to_string(ventaController.size() + 1), listado);
                if (opt != 0 && opt != -1)
                {
                    carrito.erase(carrito.begin() + opt - 1);
                    listado.erase(listado.begin() + opt - 1);
                }
            } while (opt != 0);
            opt = 2;
            break;

        case 3:
            listado.clear();
            for (VentaD x : carrito)
            {
                nombreProducto = productoController.get(x.getCodProducto()).getNombre();
                precioUnitario = x.getPrecio();
                cantProducto = x.getCantidad();
                montoProducto = x.getMonto();
                listado.push_back(nombreProducto + "\tS/" + to_string(precioUnitario) + "\t" + to_string(cantProducto) + "u\tS/" + to_string(montoProducto));
            }
            menuListado(listado, 0, "Venta #" + to_string(ventaController.size() + 1));
            break;

        case 4:
            listado.clear();
            for (VentaD x : carrito)
            {
                nombreProducto = productoController.get(x.getCodProducto()).getNombre();
                precioUnitario = x.getPrecio();
                cantProducto = x.getCantidad();
                montoProducto = x.getMonto();
                listado.push_back(nombreProducto + "\tS/" + to_string(precioUnitario) + "\t" + to_string(cantProducto) + "u\tS/" + to_string(montoProducto));
            }
            menuListado(listado, 0, "Venta #" + to_string(ventaController.size() + 1));
            if (menuConfirmar("Desea agregar una observacion a esta Venta"))
            {
                menuDatos({""}, inputs, 0, 0, "Observacion Venta #" + to_string(ventaController.size() + 1));
                observacion = inputs[0];
            }

            for (VentaD x : carrito)
            {
                tempKardex.setCantidad(x.getCantidad());
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setCodProducto(x.getCodProducto());
                tempKardex.setCodProceso(createCode("VT", ventaController.size(), 5));
                tempKardex.setComprobante(comprobante);
                tempKardex.setFechaDeEmision(fecha);
                tempKardex.setIsSalida(true);
                tempKardex.setMontoUnitario(x.getPrecio());
                tempKardex.setMotivo("~~Venta " + to_string(cantComprobantes) + "~~");
                tempKardex.setObservacion(observacion);
                kardexController.add(tempKardex);
                ventaDController.add(x);
                kardexController.saveFile();
                ventaDController.saveFile();
                montoTotal += (x.getPrecio() * x.getCantidad());
            }
            tempVenta.setCodVenta(ventaController.size());
            tempVenta.setCodCliente(clienteController.getPosDoc(clienteDNI, tipoDocumento));
            tempVenta.setCodUsuario(progController.getSesionKey());
            tempVenta.setFecha(fecha);
            tempVenta.setMonto(montoTotal);
            tempVenta.setEstado(true);
            ventaController.add(tempVenta);
            ventaController.saveFile();
            opt = 0;
            break;
        case 0:
            if (!menuConfirmar("Seguro que desea cancelar la Venta"))
                opt = -1;
            break;
        default:
            break;
        }
    } while (opt != 0);
}

void doMovimiento()
{
    int opt;
    vector<string> inputs;
    vector<string> listado;

    long long int clienteDNI;
    int codProducto;
    int cantProducto;
    double montoProducto;
    string comprobante;
    string codigoMovimiento;
    string fecha;
    string motivo;
    string observacion = "-";

    int cantComprobantes = kardexController.getCantidadComprobante(true);

    vector<CompraD> carrito;
    vector<kardex> kardexCarrito;
    CompraD tempCompraD;
    kardex tempKardex;

    // FECHA
    if (menuConfirmar("Desea usar la fecha de hoy para registrar el Movimiento"))
    {
        cin.ignore();
        fecha = currentDateTime().substr(0, currentDateTime().find(' '));
    }
    else
    {
        cin.ignore();
        do
        {
            cout << kardexController.validarFormatoFecha(inputs[0]);
            system("pause");
            inputs.clear();
            menuDatos({"Fecha"}, inputs, 0, 0, "'Salir' para cancelar");
        } while (!kardexController.validarFormatoFecha(inputs[0]) || aMinuscula(inputs[0]) == "salir");
        if (aMinuscula(inputs[0]) == "salir")
            return;
        fecha = inputs[0];
    }

    inputs.clear();
    // DOCUMENTOS
    do
    {
        inputs.clear();
        menuDatos({"Documento"}, inputs, 0, 0, "Datos del Documento Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Clientes
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
    } while (!esNumero(inputs[0]) || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    clienteDNI = stoll(inputs[0]);
    inputs.clear();
    // COMPROBANTE VENTA PRODUCTO

    cin.ignore();
    inputs.clear();
    opt = menu("Comprobante Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Boleta de Venta Automatica", "Factura de Venta Automatica", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            cin.ignore();
            inputs.clear();
            menuDatos({"Comprobante de Compra"}, inputs, 0, 0, "Datos del Comprobante Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));
        comprobante = inputs[0];
    case 2:
        comprobante = createCode("BV", kardexController.getCantidadComprobanteVenta(true));
        break;
    case 3:
        comprobante = createCode("FV", kardexController.getCantidadComprobanteVenta(false));
        break;
    case 4:
        comprobante = "-";
    default:
        return;
        break;
    }

    // CODIGO MOVIMIENTO

    cin.ignore();
    inputs.clear();
    opt = menu("Codigo Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Automatico", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            cin.ignore();
            inputs.clear();
            menuDatos({"Codigo de Movimiento"}, inputs, 0, 0, "Codigo del Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (aMinuscula(inputs[0]) == "salir")
                return;
        } while (!menuConfirmar("Confirma que el comprobante de compra sea " + inputs[0]));
    case 2:
        codigoMovimiento = createCode("MT", kardexController.getCantidadComprobante(false, true), 5);
        break;
    case 3:
        codigoMovimiento = "-";
    default:
        return;
        break;
    }

    //  PRODUCTO
    do
    {
        inputs.clear();
        menuDatos({"Producto"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (stoi(inputs[0]) >= productoController.getNewCodProducto())
            menuError({"Producto no registrado"});
    } while (!esNumero(inputs[0]) || stoi(inputs[0]) >= productoController.getNewCodProducto() || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    codProducto = stoi(inputs[0]);
    inputs.clear();

    bool isSalida = menuConfirmar("El movimiento es una reduccion en el inventario");

    // CANTIDAD PRODUCTO
    do
    {
        inputs.clear();
        cin.ignore();
        menuDatos({"Cantidad"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
        if (inputs[0].size() < 0)
            menuError({"Cantidad Invalida"});
    } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    cantProducto = stoi(inputs[0]);
    inputs.clear();

    // PRECIO PRODUCTO

    cin.ignore();
    inputs.clear();
    opt = menu("Agregar precio al Producto, Movimiento #" + to_string(kardexController.getVector().size() + 1), {"Manualmente", "Automatico", "Ninguno"});
    switch (opt)
    {
    case 1:
        do
        {
            inputs.clear();
            menuDatos({"Costo Unitario"}, inputs, 0, 0, "Producto Movimiento #" + to_string(kardexController.getVector().size() + 1)); // Producto
            if (!esNumero(inputs[0]))
                menuError({"Introduzca un valor numerico"});
            if (inputs[0].size() < 0)
                menuError({"Cantidad Invalida"});
        } while (!esNumero(inputs[0]) || inputs[0].size() < 0 || aMinuscula(inputs[0]) == "salir");

        if (aMinuscula(inputs[0]) == "salir")
            return;
        montoProducto = stoi(inputs[0]);
    case 2:
        montoProducto = productoController.get(codProducto).getPrecioUnitario();
        break;
    case 3:
        montoProducto = 0;
        break;
    default:
        return;
        break;
    }

    inputs.clear();

    tempCompraD.setCodCompra(compraController.size());
    tempCompraD.setCodProducto(codProducto);
    tempCompraD.setCantidad(cantProducto);
    tempCompraD.setPrecio(montoProducto);

    carrito.push_back(tempCompraD);

    ///////////////////////////////////////////////////////////

    cin.ignore();
    menuDatos({""}, inputs, 0, 0, "Motivo Movimiento #" + to_string(kardexController.getVector().size() + 1));
    motivo = inputs[0];

    if (menuConfirmar("Desea agregar una observacion a este Movimiento"))
    {
        cin.ignore();
        menuDatos({""}, inputs, 0, 0, "Observacion Movimiento #" + to_string(kardexController.getVector().size() + 1));
        observacion = inputs[0];
    }

    for (CompraD x : carrito)
    {
        tempKardex.setCantidad(x.getCantidad());
        tempKardex.setMontoUnitario(x.getPrecio());
        tempKardex.setCodProducto(x.getCodProducto());
        tempKardex.setCodProceso(codigoMovimiento);
        tempKardex.setComprobante(comprobante);
        tempKardex.setFechaDeEmision(fecha);
        tempKardex.setIsSalida(isSalida);
        tempKardex.setMontoUnitario(x.getPrecio());
        tempKardex.setMotivo(motivo);
        tempKardex.setObservacion(observacion);
        kardexController.add(tempKardex);
        kardexController.saveFile();
    }
}

void doRegistrarRetiroCaja()
{
    double monto;
    string observacion;
    vector<string> inputs;
    if (!progController.getActiveSesion() || !progController.getIsSupervisor())
    {
        menuError({"~-NECESITAS TENER UNA SESI�N DE SUPERVISOR O ADMINISTRADOR INICIADA-~"});
        return;
    }
    do
    {
        inputs.clear();
        menuDatos({"Monto de Retiro"}, inputs, 0, 0, "Retiro de Efectivo"); // Producto
        if (!esNumero(inputs[0]))
            menuError({"Introduzca un valor numerico"});
    } while (!esNumero(inputs[0]) || aMinuscula(inputs[0]) == "salir");

    if (aMinuscula(inputs[0]) == "salir")
        return;

    monto = stoi(inputs[0]);

    inputs.clear();
    if (menuConfirmar("Desea agregar una observacion a este Movimiento"))
    {
        cin.ignore();
        menuDatos({""}, inputs, 0, 0, "Observacion - Retiro de Efectivo");
        observacion = inputs[0];
    }

    inputs.clear();

    kardex obj(currentDateTime().substr(0, currentDateTime().find(' ')), 1, -1, monto, createCode("RT", kardexController.getMovimientosRetiros().size(), 5),
               createCode("RT", kardexController.getMovimientosRetiros().size(), 5), true,
               "RETIRO DE EFECTIVO ( S/." + to_string(monto) + " ) POR " + userController.get(progController.getSesionKey()).getNombre() +
                   " " + userController.get(progController.getSesionKey()).getApellidos(),
               observacion);
    kardexController.add(obj);
    kardexController.saveFile();
}

void askEstadoCaja()
{
    menuListado({"S/" + to_string(kardexController.getEstadoCaja())}, 0, "_SALDO ACTUAL_", true);
}

void doConsultarRegistro(int cod)
{
    int opt;
    int codUsuario = cod;
    vector<Venta> registro;
    vector<string> listaRegistro;
    for (int i = 0; i < ventaController.size(); i++)
    {
        Venta vTemp = ventaController.get(i);
        if (vTemp.getCodUsuario() == codUsuario)
            registro.push_back(vTemp);
    }
    if (registro.size() == 0)
    {
        menuError({"Aun no se hicieron ventas"});
    }
    else
    {
        for (Venta x : registro)
            listaRegistro.push_back(to_string(x.getCodVenta()) + "\tS/" + to_string(x.getMonto()));
        do
        {
            vector<string> listaVenta;
            opt = menu("_REGISTRO DE VENTAS_", listaRegistro);
            switch (opt)
            {
            case -1:
                break;
            case 0:
                break;
            default:
                Venta vTemp;
                Cliente cTemp;
                vector<VentaD> registroVentaD;
                vTemp = ventaController.get(opt - 1);
                cTemp = clienteController.get(vTemp.getCodCliente() - 1);
                listaVenta.push_back("Nombre del Cliente: " + cTemp.getNombre());
                listaVenta.push_back("DNI del Cliente: " + cTemp.getDocumento());
                listaVenta.push_back("Productos:");
                for (int i = 0; i < ventaDController.size(); i++)
                {
                    VentaD vDTemp = ventaDController.get(i);
                    if (vDTemp.getCodVenta() == opt)
                    {
                        Producto pTemp;
                        pTemp = productoController.get(vDTemp.getCodProducto() - 1);
                        listaVenta.push_back("\t" + pTemp.getNombre() + "\tS/" + to_string(vDTemp.getPrecio()) + "\t" + to_string(vDTemp.getCantidad()) + "u\tS/" + to_string(vDTemp.getMonto()));
                    }
                }
                listaVenta.push_back("Monto total: S/" + to_string(vTemp.getMonto()));
                menuListado(listaVenta);
                break;
            }
        } while (opt != 0);
    }
}

void doBuscarRegistro()
{
    int opt;
    vector<string> usuarios;
    for (int i = 0; i < userController.size(); i++)
    {
        Usuario uTemp = userController.get(i);
        usuarios.push_back(uTemp.getUsername() + "\t" + uTemp.getNombre() + " " + uTemp.getApellidos());
    }
    do
    {
        opt = menu("_USUARIOS_", usuarios);
        switch (opt)
        {
        case -1:
            break;
        case 0:
            break;
        default:
            doConsultarRegistro(opt - 1);
            break;
        }
    } while (opt != 0);
}

void askInventario()
{
    int opt;
    int cod;
    int j;
    string producto;
    Producto temp;
    vector<string> listado;
    vector<string> listaProductos;
    for (int i = 0; i < productoController.size(); i++)
        listaProductos.push_back(productoController.get(i).getNombre());

    if (listaProductos.size() != 0)
    {
        do
        {
            producto = menuBusqueda(listaProductos, 0, "_Buscar productos_");
            if (producto != "salir")
            {
                for (int i = 0; i < productoController.size(); i++)
                    if (productoController.get(i).getNombre() == producto)
                        cod = productoController.get(i).getCodProducto();

                opt = menu("Selecciona que deseas hacer", {"Consultar datos del producto", "Consultar k�rdex del producto"});

                switch (opt)
                {
                case 1:
                    j = 1;
                    temp = productoController.get(cod);
                    listado={"Codigo de producto: " + to_string(temp.getCodProducto()),
                                           "Marca: " + marcaController.get(temp.getCodMarca()).getNombreMarca(),
                                           "Nombre: " + temp.getNombre(),
                                           "Precio unitario: S/" + to_string(temp.getPrecioUnitario()),
                                           "Unidades disponibles: " + to_string(temp.getStock())};
                    for (Componente x : temp.getVectorComponentes())
                    {
                        listado.push_back("Componente[" + to_string(j) + "]: " + x.getNombre() + "\t" + x.getCantidad());
                        j++;
                    }
                    menuListado(listado, 0, aMayuscula(temp.getNombre()), true);

                    break;
                case 2:
                    showKardex(cod);
                    break;
                default:
                    break;
                }
            }

        } while (producto != "salir");
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
        menuError({"Necesitas iniciar sesi�n como Supervisor"});
        if (!doIniciarSesion(false, temporal))
            return;
        else if (temporal != "Supervisor" && temporal != "Admin")
            return;
    }

    string producto;
    vector<string> listaProductos;
    for (int i = 0; i < productoController.size(); i++)
        listaProductos.push_back(productoController.get(i).getNombre());
    do
    {
        opt = menu("_Busqueda de Producto_", {"Por codigo", "Por nombre"});
        switch (opt)
        {
        case 1:
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
                        menuError({"Introduce un valor num�rico"});
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
                    }
                }
            } while (!salida);
            codigo = stoi(inputs[0]);
            break;
        case 2:
            producto = menuBusqueda(listaProductos, 0, "_Buscar productos_");
            if (producto != "salir")
            {
                for (int i = 0; i < productoController.size(); i++)
                    if (productoController.get(i).getNombre() == producto)
                    {
                        codigo = productoController.get(i).getCodProducto();
                        break;
                    }
            }
            break;
        default:
            break;
        }
    } while (opt != 1 && opt != 2 && opt != 0);
    if (opt == 0)
        return;

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
                    menuDatos({"Nuevo c�digo de marca"}, inputs);
                    temporal = inputs[0];
                    if (!esNumero(temporal))
                    {
                        menuError({"Introduce un valor num�rico"});
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
                        menuError({"Introduce un valor num�rico"});
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
        menuError({"Necesitas iniciar sesi�n como Supervisor"});
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
        ;
        menuDatos({"Nombre del Producto"}, inputs, 0, 0, "_PRODUCTO [" + to_string(codigo + 1) + "]_");
        string nombre = inputs[0];
        do
        {
            inputs.clear();
            ;
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
                ;
                do
                {
                    inputs.clear();
                    menuDatos({"Precio S/"}, inputs);
                    if (!esNumero(inputs[0]))
                        menuError({"Introduce un valor num�rico"});
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
        menuError({"Necesitas iniciar sesi�n como Supervisor"});
        if (!doIniciarSesion(false, temporal))
            return;
        else if (temporal != "Supervisor" && temporal != "Admin")
            return;
    }
    do
    {
        codigo = marcaController.getNewCodMarca();
        inputs.clear();
        ;
        menuDatos({"Nombre de la marca"}, inputs, 0, 0, "_MARCA [" + to_string(codigo + 1) + "]_");
        Marca marca(codigo, inputs[0]);
        marcaController.add(marca);
    } while (menuConfirmar("Desea agregar una nueva marca"));
    marcaController.saveFile();
}

long long int doRegistrarTercero(bool isCliente, long long int documento = -1)
{
    string tipoDocumento, strInput, nombreTercero;
    int docSize, opt;
    long long int numeroDocumento;
    vector<string> options, inputs;
    Cliente objCliente;
    Proveedor objProveedor;
    bool duplicado;

    if (documento != -1)
        numeroDocumento == documento;

    // INTRODUCIR NUMERO DOCUMENTO
    strInput = "0";
    do
    {
        do
        {
            if (isCliente)
            {
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
                    return -1;
            }
            else
            {
                tipoDocumento = "RUC";
                docSize = 11;
            }
            inputs.clear();
            if (documento < 0)
            {
                menuDatos({"Numero de documento"}, inputs, 0, 0, "_DOCUMENTO_ -('Salir' para salir)");
                strInput = inputs[0].substr(0, inputs[0].find(' '));
            }
            else
            {
                strInput = to_string(documento);
            }

            if (aMinuscula(strInput) == "salir")
                return -1;

            if ((int)strInput.size() != docSize)
            {
                options = {"~-Los documentos tipo " + tipoDocumento + " deben contener " + to_string(docSize) + " digitos-~", "~VUELVA A INGRESAR SU NUMERO DE DOCUMENTO~"};
                menuError(options, 1);
                documento = -1;
            }
            if (!esNumero(strInput))
                menuError({"~[[INTRODUCE UN VALOR NUMERICO]]~"});
        } while (!esNumero(strInput) || (int)strInput.size() != docSize);

        numeroDocumento = stoll(strInput);
        if (isCliente)
        {
            if (clienteController.getPosDoc(numeroDocumento, tipoDocumento) != -1)
            {
                duplicado = true;
            }
            else
                duplicado = false;
        }
        else
        {
            if (proveedorController.getPosRUC(numeroDocumento) != -1)
                duplicado = true;
            else
                duplicado = false;
        }
        if (duplicado)
        {
            menuError({"Ya Registrado, 'salir' para salir"});
            documento = -1;
        }
    } while (duplicado);

    // NOMBRE
    do
    {
        inputs.clear();
        menuDatos({"Nombre"}, inputs, 0, 0, ""); // Producto
        if (aMinuscula(inputs[0]) == "salir")
            return -1;
    } while (!menuConfirmar("Confirma que el nombre es " + inputs[0]));

    nombreTercero = inputs[0];
    inputs.clear();

    if (isCliente)
    {
        objCliente.setCodCliente(clienteController.size());
        objCliente.setTipoDocumento(tipoDocumento);
        objCliente.setDocumento(numeroDocumento);
        objCliente.setNombre(nombreTercero);
        clienteController.add(objCliente);
        clienteController.saveFile();
    }
    else
    {
        objProveedor.setCodProveedor(proveedorController.size());
        objProveedor.setTipoDocumento(tipoDocumento);
        objProveedor.setDocumento(numeroDocumento);
        objProveedor.setNombre(nombreTercero);
        proveedorController.add(objProveedor);
        proveedorController.saveFile();
    }
    return numeroDocumento;
}

void doActualizarInventario()
{
    for (int i = 0; i < productoController.size(); i++)
    {
        Producto objProducto = productoController.get(i);
        objProducto.setStock(kardexController.getCantidadProducto(i));
        productoController.modify(objProducto, i);
    }
    productoController.saveFile();
}