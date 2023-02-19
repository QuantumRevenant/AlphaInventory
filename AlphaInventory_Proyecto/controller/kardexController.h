#ifndef KARDEXCONTROLLER_H
#define KARDEXCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/kardex.cpp"

using namespace std;

/*

*/

class KardexController
{
private:
    vector<kardex> vectorKardex;

public:
    KardexController();

    void add(kardex);
    void modify(kardex, int);
    kardex get(int);
    vector<kardex> getVector();

    void saveFile();
    void saveFileAll();
    void getFile();

    bool validarFormatoFecha(string);
    vector<kardex> getMovimientosProducto(int);
    vector<kardex> getMovimientosComprobante(bool, bool);
    vector<kardex> getMovimientosRetiros();
    vector<kardex> getMovimientosProducto(int, bool);

    int getEstadoCaja();
    int getCantidadComprobanteVenta(bool);
    int getCantidadComprobante(bool, bool);
    int getCantidadProducto(int);
};

KardexController::KardexController() { getFile(); }

void KardexController::add(kardex obj) { vectorKardex.push_back(obj); }
void KardexController::modify(kardex obj, int pos) { vectorKardex[pos] = obj; }
kardex KardexController::get(int pos) { return vectorKardex[pos]; }
vector<kardex> KardexController::getVector() { return vectorKardex; }

void KardexController::saveFile()
{
    try
    {
        fstream archivoKardex;
        archivoKardex.open("../data/movimientos.csv", ios::app);
        if (archivoKardex.is_open())
        {
            kardex obj = vectorKardex.back();
            string isSalida = obj.getIsSalida() ? "true" : "false";
            archivoKardex << obj.getFechaDeEmision() << ","
                          << obj.getCantidad() << ","
                          << obj.getCodProducto() << ","
                          << obj.getCodProceso() << ","
                          << obj.getComprobante() << ","
                          << isSalida << ","
                          << obj.getMotivo() << ","
                          << obj.getObservacion() << ","
                          << obj.getMontoUnitario() << ",";
            archivoKardex << endl;
        }
        archivoKardex.close();
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void KardexController::saveFileAll()
{
    try
    {
        fstream archivoKardex;
        archivoKardex.open("../data/movimientos.csv", ios::out);
        if (archivoKardex.is_open())
        {
            for (kardex obj : vectorKardex)
            {
                string isSalida = obj.getIsSalida() ? "true" : "false";
                archivoKardex << obj.getFechaDeEmision() << ","
                              << obj.getCantidad() << ","
                              << obj.getCodProducto() << ","
                              << obj.getCodProceso() << ","
                              << obj.getComprobante() << ","
                              << isSalida << ","
                              << obj.getMotivo() << ","
                              << obj.getObservacion() << ","
                              << obj.getMontoUnitario() << ",";
                archivoKardex << endl;
            }
        }
        archivoKardex.close();
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void KardexController::getFile()
{
    int i;
    size_t posi; // Cantidad maxima
    string linea;
    vector<string> temporal; // Cantidad de columnas
    fstream archivoKardex;
    archivoKardex.open("../data/movimientos.csv", ios::in);
    if (archivoKardex.is_open())
    {
        while (!archivoKardex.eof() && getline(archivoKardex, linea))
        {
            temporal.clear();
            i = 0;
            while ((posi = linea.find(",")) != string::npos)
            {                                              /*string::npos es -1, termina cuando llega a este punto*/
                temporal.push_back(linea.substr(0, posi)); /*posi = Es la cantidad de caracteres antes del ;*/
                linea.erase(0, posi + 1);                  // borra la palabra de la primera posici�n encontrada   y con el +1 incluye hasta el ; y luego borra ese elemento, para que en la siguiente iteracion iniciar con la siguiente palabra y de ese modo seguir el proceso ,
                i++;
            }
            // Asignando los valores al vector

            bool isSalida = (temporal[5] == "true");
            kardex objKardex(temporal[0], stoi(temporal[1]), stoi(temporal[2]), stoi(temporal[8]), temporal[3], temporal[4], isSalida, temporal[6], temporal[7]);
            cout << "Movimiento " << temporal[0] << " cargado..." << endl;
            Sleep(1);
            add(objKardex);
        }
    }
    archivoKardex.close();
}

bool KardexController::validarFormatoFecha(string entrada)
{
    size_t posi;
    int i = 0;
    vector<string> temporal;

    int e = 0;

    entrada.push_back('/');
    while ((posi = entrada.find("/")) != string::npos)
    {                                                /*string::npos es -1, termina cuando llega a este punto*/
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
vector<kardex> KardexController::getMovimientosProducto(int cod)
{
    vector<kardex> salida;
    for (kardex x : vectorKardex)
    {
        cout << x.getCantidad() << endl;
        if (x.getCodProducto() == cod)
            salida.push_back(x);
    }
    system("pause");
    return salida;
}
vector<kardex> KardexController::getMovimientosProducto(int cod, bool isSalida)
{
    vector<kardex> salida;
    vector<kardex> movimientos;
    movimientos = getMovimientosProducto(cod);
    for (kardex x : movimientos)
    {
        if (x.getIsSalida() == isSalida)
            salida.push_back(x);
    }
}

int KardexController::getEstadoCaja()
{
    int salida = 0;
    vector<double> suma, resta;
    for (kardex x : vectorKardex)
    {
        if(x.getCodProceso().substr(0, 2) == "VT")
            suma.push_back(x.getMontoUnitario()*x.getCantidad());
        else if(x.getCodProceso().substr(0, 2) == "RT")
            resta.push_back(x.getMontoUnitario()*x.getCantidad());
    }
    for (double x : suma)
        salida += x;
    for (double x : resta)
        salida -= x;
    return salida;
}
vector<kardex> KardexController::getMovimientosRetiros()
{
    vector<kardex> salida;
    string iniciales ="RT";
    for (kardex x : vectorKardex)
    {
        if (x.getCodProceso().substr(0, 2) == iniciales)
            salida.push_back(x);
    }
    return salida;
}

vector<kardex> KardexController::getMovimientosComprobante(bool isVenta, bool isMovimiento = false)
{
    vector<kardex> salida;
    string iniciales = isMovimiento ? "MT" : isVenta ? "VT"
                                                     : "CP";
    for (kardex x : vectorKardex)
    {
        if (x.getCodProceso().substr(0, 2) == iniciales)
            salida.push_back(x);
    }
    return salida;
}
int KardexController::getCantidadComprobanteVenta(bool isBoleta)
{
    vector<kardex> salida, entrada;
    string iniciales = isBoleta ? "BV" : "FV";
    entrada = getMovimientosComprobante(true);
    for (kardex x : entrada)
    {
        if (x.getComprobante().substr(0, 2) == iniciales)
            salida.push_back(x);
    }
    return salida.size();
}
int KardexController::getCantidadComprobante(bool isVenta, bool isMovimiento = false)
{
    vector<kardex> comprobantes;
    comprobantes = getMovimientosComprobante(isVenta, isMovimiento);
    return comprobantes.size();
}
int KardexController::getCantidadProducto(int cod)
{
    int salida;
    vector<int> aSumar, aRestar;
    vector<kardex> movimientos;
    movimientos = getMovimientosProducto(cod);
    for (kardex x : movimientos)
    {
        if (x.getIsSalida())
            aRestar.push_back(x.getCantidad());
        else
            aSumar.push_back(x.getCantidad());
    }

    for (int x : aSumar)
        salida += x;
    for (int x : aRestar)
        salida -= x;
    cout << salida << endl;
    system("pause");
    return salida;
}

#endif