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

class kardexController
{
private:
    vector<kardex> vectorKardex;

public:
    kardexController();

    void add(kardex);
    void modify(kardex, int);
    kardex get(int);
    vector<kardex> getVector();

    void saveFile();
    void saveFileAll();
    void getFile();

    bool validarFormatoFecha(string);
    vector<kardex> getMovimientosProducto(int);
    vector<kardex> getMovimientosComprobante(bool);
    int getCantidadComprobante(bool);
    int getCantidadProducto(int);
};

kardexController::kardexController() { getFile(); }

void kardexController::add(kardex obj) { vectorKardex.push_back(obj); }
void kardexController::modify(kardex obj, int pos) { vectorKardex[pos] = obj; }
kardex kardexController::get(int pos) { return vectorKardex[pos]; }
vector<kardex> kardexController::getVector() { return vectorKardex; }

void kardexController::saveFile()
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
                          << obj.getObservacion() << ",";
            archivoKardex << endl;
        }
        archivoKardex.close();
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void kardexController::saveFileAll()
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
                              << obj.getObservacion() << ",";
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
void kardexController::getFile()
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
            i = 0;
            while ((posi = linea.find(",")) != string::npos)
            {                                              /*string::npos es -1, termina cuando llega a este punto*/
                temporal.push_back(linea.substr(0, posi)); /*posi = Es la cantidad de caracteres antes del ;*/
                linea.erase(0, posi + 1);                  // borra la palabra de la primera posici�n encontrada   y con el +1 incluye hasta el ; y luego borra ese elemento, para que en la siguiente iteracion iniciar con la siguiente palabra y de ese modo seguir el proceso ,
                i++;
            }
            // Asignando los valores al vector

            bool isSalida = (temporal[5] == "true");
            kardex objKardex(temporal[0], stoi(temporal[1]), stoi(temporal[2]), temporal[3], temporal[4], isSalida, temporal[6], temporal[7]);
            cout << "Movimiento " << temporal[0] << " cargado..." << endl;
            Sleep(1);
            add(objKardex);
        }
    }
    archivoKardex.close();
}

bool kardexController::validarFormatoFecha(string entrada)
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
vector<kardex> kardexController::getMovimientosProducto(int cod)
{
    vector<kardex> salida;
    for(kardex x:vectorKardex)
    {
        if(x.getCodProducto()==cod)
            salida.push_back(x);
    }
    return salida;
}
vector<kardex> kardexController::getMovimientosComprobante(bool isVenta)
{
    vector<kardex> salida;
    string iniciales=isVenta?"VT":"CP";
    for(kardex x:vectorKardex)
    {
        if(x.getCodProceso().substr(0,2)==iniciales)
            salida.push_back(x);
    }
    return salida;
}
int kardexController::getCantidadComprobante(bool isVenta)
{
    vector<kardex> comprobantes;
    comprobantes=getMovimientosComprobante(isVenta);
    return comprobantes.size();
}
int kardexController::getCantidadProducto(int cod)
{
    int salida;
    vector<int> aSumar,aRestar;
    vector<kardex> movimientos;
    movimientos=getMovimientosProducto(cod);
    for(kardex x:movimientos)
    {
        if(x.getIsSalida())
            aRestar.push_back(x.getCantidad());
        else
            aSumar.push_back(x.getCantidad());
    }

    for(int x:aSumar)
        salida+=x;
    for(int x:aRestar)
        salida-=x;
    
    return salida;
}

#endif