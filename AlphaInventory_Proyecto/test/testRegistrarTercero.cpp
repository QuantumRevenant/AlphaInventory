#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>
#include "../controller/controllers.h"
#include "../model/models.h"

ProveedorController proveedorController;
ClienteController clienteController;

using namespace std;

/*

*/

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

    // INTRODUCIR NUMERO DOCUMENTO
    strInput = "0";
    do
    {
        do
        {
            inputs.clear();
            if (documento < 0)
            {
                menuDatos({"Numero de documento"}, inputs, 0, 0, "_" + tipoDocumento + "_ -('Salir' para salir)");
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
            if (clienteController.getPosDoc(numeroDocumento,tipoDocumento) != -1)
                duplicado = true;
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

int main(int argc, char *argv[])
{
    cout<<doRegistrarTercero(true)<<endl;
    system("pause");
    return 0;
}