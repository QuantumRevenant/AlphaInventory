#include <iostream>
#include <string>
#include <vector>
#include "../model/kardex.cpp"
#include "../model/FuncionesGenerales.h"
using namespace std;

/*

*/

bool validarFormatoFecha(string entrada)
{
    size_t posi;
    int i = 0;
    vector<string> temporal;

    int e = 0;

    entrada.push_back('/');
    while ((posi = entrada.find("/")) != string::npos)
    {                                              /*string::npos es -1, termina cuando llega a este punto*/
        temporal.push_back(entrada.substr(0, posi)); /*posi = Es la cantidad de caracteres antes del ;*/
        entrada.erase(0, posi + 1);                  // borra la palabra de la primera posici�n encontrada   y con el +1 incluye hasta el ; y luego borra ese elemento, para que en la siguiente iteracion iniciar con la siguiente palabra y de ese modo seguir el proceso ,
        i++;
    }
    if (temporal.size() != 3)
        return false;
    if (temporal[0].size() != 2 || temporal[1].size() != 2 || temporal[2].size() != 4)
        return false;
    if (!esNumero(temporal[0]) || !esNumero(temporal[1]) || !esNumero(temporal[2]))
        return false;
    if ((stoi(temporal[0]) < 1 || stoi(temporal[0]) > 31) || (stoi(temporal[1]) < 1 || stoi(temporal[1]) > 12))
        return false;
    if (!(stoi(temporal[1]) == 1 || stoi(temporal[1]) == 3 || stoi(temporal[1]) == 5 || stoi(temporal[1]) == 7 || stoi(temporal[1]) == 8 || stoi(temporal[1]) == 10 || stoi(temporal[1]) == 12))
    {
        if (stoi(temporal[0]) > 30)
            return false;
        if (stoi(temporal[1]) == 2)
        {
            if (stoi(temporal[0]) > 29)
                return false;
            if (!((stoi(temporal[2]) % 4 == 0 && stoi(temporal[2]) % 100 != 0) || stoi(temporal[2]) % 400 == 0))
                if (stoi(temporal[0]) > 28)
                    return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    string input;
    do
    {
        cin >> input;
    } while (!validarFormatoFecha(input));

    cout << currentDateTime().substr(0, currentDateTime().find(' ')) << endl;
    cout << currentDateTime() << endl;
    kardex objKardex(currentDateTime().substr(0, currentDateTime().find(' ')), 5, 0, "VN00000", "EB01-1", true, "VENTA", "VENTA DE PRUEBA");

    kardex objSalida = objKardex;
    cout << objSalida.getFechaDeEmision() << endl;
    cout << objSalida.getCantidad() << endl;
    cout << objSalida.getCodProducto() << endl;
    cout << objSalida.getCodProceso() << endl;
    cout << objSalida.getComprobante() << endl;
    string salida = objSalida.getIsSalida() ? "True" : "False";
    cout << salida << endl;
    cout << objSalida.getMotivo() << endl;
    cout << objSalida.getObservacion() << endl;

    return 0;
}