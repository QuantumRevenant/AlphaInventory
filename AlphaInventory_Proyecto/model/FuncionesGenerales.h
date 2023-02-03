#ifndef FUNCIONESGENERALES_H
#define FUNCIONESGENERALES_H

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

#define ENTER 13
#define BACKSPACE 8

std::string aMayuscula(std::string cadena)
{
    for (int i = 0; i < (int)cadena.length(); i++)
    {
        cadena[i] = std::toupper(cadena[i]);
    }
    return cadena;
}

std::string aMinuscula(std::string cadena)
{
    for (int i = 0; i < (int)cadena.length(); i++)
    {
        cadena[i] = std::tolower(cadena[i]);
    }
    return cadena;
}

bool esNumero(std::string cadena)
{
    bool resultado = true;
    int i = 0;
    while (i < (int)cadena.length())
    {
        if (!isdigit(cadena[i])&&cadena[i]!='-'&&cadena[i]!='.')
            resultado = false;
        i++;
    }

    return resultado;
}

int subCadenaComunMasLarga(std::string cadena1, std::string cadena2)
{
    int ans = 0;

    for (int i = 0; i < (int)cadena1.length(); i++)
    {
        for (int j = 0; j < (int)cadena2.length(); j++)
        {
            int k = 0;
            while ((i + k) < (int)cadena1.length() && (j + k) < (int)cadena2.length() && cadena1[i + k] == cadena2[j + k])
            {
                k = k + 1;
            }

            ans = std::max(ans, k);
        }
    }
    return ans;
}

float Promediar(float datos[], int cantidadAPromediar)
{
    float acumulador=0, promedio=0;
    for(int i=0;i<cantidadAPromediar;i++)
    {
        acumulador=acumulador+datos[i];
    }

    if(cantidadAPromediar>0)
    promedio=acumulador/cantidadAPromediar;

    return promedio;
}

float PromediarMayor0(float datos[], int cantidadDatos)
{
    int cantidadAPromediar=0;
    float aPromediar[999], promedio;

    for(int i=0;i<cantidadDatos;i++)
    {
        if(datos[i]>0)
        {
            aPromediar[cantidadAPromediar]=datos[i];
            cantidadAPromediar++;
        }
    }

    promedio=Promediar(aPromediar,cantidadAPromediar);

    return promedio;
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
void getValue(string mensaje, float *dato)
{
    cout << mensaje;
    cin >> *dato;
}
bool confirmar(string message,string message2=" ")
{
    string opt;
    cout << endl
         << endl
         << "¿Seguro que desea " << message << "?"<<message2<<"(Confirmar: S/s)" << endl;
    cin >> opt;
    if (aMinuscula(opt) == "s")
        return true;
    else
        return false;
}
#define ENTER 13
#define BACKSPACE 8

void doEndline(int i)
{
    for (int j = 0; j < i; j++)
    {
        cout << endl;
    }
}

void doTab(int i)
{
    for (int j = 0; j < i; j++)
    {
        cout << "\t";
    }
}

string doTab(int i, string entrada)
{
    string salida = entrada;
    for (int j = 0; j < i; j++)
    {
        salida = salida + "\t";
    }
    return salida;
}

string enterContrasena()
{
    string password;
    char caracter;
    caracter = getch();
    password = "";
    while (caracter != ENTER)
    {
        if (caracter != BACKSPACE)
        {
            password.push_back(caracter);
            cout << "*";
        }
        else
        {
            if (password.length() > 0)
            {
                cout << "\b \b";
                password = password.substr(0, password.length() - 1);
            }
        }
        caracter = getch();
    }
    return password;
}
#endif