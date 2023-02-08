#ifndef FUNCIONESGENERALES_H
#define FUNCIONESGENERALES_H

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

#define ENTER 13
#define BACKSPACE 8

string aMayuscula(string);
string aMinuscula(string);
bool esNumero(string);
int subCadenaComunMasLarga(string, string);
float Promediar(float[], int);
float PromediarMayor0(float[], int);
void getValue(string, int *);
void getValue(string, string *);
void getValue(string, float *);
bool confirmar(string, string, int);
void doEndline(int);
void doTab(int);
string doTab(int, string);
string enterContrasena();
void gotoxy(int, int);
void centrarTexto(string, int, bool, bool, int, int);
#define XSIZECMD 120-1
#define YSIZECMD 30-1

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
        if (!isdigit(cadena[i]) && cadena[i] != '-' && cadena[i] != '.')
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
    float acumulador = 0, promedio = 0;
    for (int i = 0; i < cantidadAPromediar; i++)
    {
        acumulador = acumulador + datos[i];
    }

    if (cantidadAPromediar > 0)
        promedio = acumulador / cantidadAPromediar;

    return promedio;
}
float PromediarMayor0(float datos[], int cantidadDatos)
{
    int cantidadAPromediar = 0;
    float aPromediar[999], promedio;

    for (int i = 0; i < cantidadDatos; i++)
    {
        if (datos[i] > 0)
        {
            aPromediar[cantidadAPromediar] = datos[i];
            cantidadAPromediar++;
        }
    }

    promedio = Promediar(aPromediar, cantidadAPromediar);

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
bool confirmar(string message, string message2 = " ", int hoffset = 0)
{
    string opt;
    cout << endl
         << endl
         << doTab(hoffset, "") << "¿Seguro que desea " << message << "?" << message2 << "(Confirmar: S/s)" << endl;
    cout << doTab(hoffset, "") << ">_ ";
    cin >> opt;
    if (aMinuscula(opt) == "s")
        return true;
    else
        return false;
}
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

#define ENTER 13
#define BACKSPACE 8
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

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}
void centrarTexto(string message, int val, bool horizontal, bool vertical, int offsetx = 0, int offsety = 0)
{
    int x=(XSIZECMD-size(message))/2;
    int y=YSIZECMD/2;
    if(horizontal && vertical)
    {
        gotoxy(x+offsetx,y+offsety);
        cout<<message; 
    }
}
void dibujarCuadro()
{
    for (int i = 0; i < XSIZECMD; i++)
    {
        string decorador="-";
        gotoxy(i,0);
        cout<<decorador;
        gotoxy(i,YSIZECMD);
        cout<<decorador;
    }
    for (int i = 0; i < YSIZECMD; i++)
    {
        string decorador="|";
        gotoxy(0,i);
        cout<<decorador;
        gotoxy(XSIZECMD,i);
        cout<<decorador;
    }
    cout<<endl<<endl;
    
}