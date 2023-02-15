#ifndef FUNCIONESGENERALES_H
#define FUNCIONESGENERALES_H

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include "../controller/Encrypter/sha256.cpp"

using namespace std;

#define ENTER 13
#define BACKSPACE 8
char baseColor[] = "0f";

string aMayuscula(string);
string aMinuscula(string);
bool esNumero(string);
int subCadenaComunMasLarga(string, string);
float Promediar(float[], int);
float PromediarMayor0(float[], int);
string currentDateTime();
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
void alinearXTexto(string, int, bool, int, int, bool);
void dibujarCuadro();
int menu(string, vector<string>);
void esquinarTexto(string, int, bool, bool, bool);

#define XSIZECMD 120
#define YSIZECMD 30

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
    bool resultado = true, point = false;
    int i = 0;
    string salida;
    int cantidadGuiones = 0, cantidadPuntos = 0;
    if (cadena.size() == 0)
        return false;
    if (cadena.size() == 1 && (cadena[0] == '.' || cadena[0] == '-'))
        return false;
    for (char x : cadena)
    {
        if (!isdigit(x) && x != '-' && x != '.')
            return false;
        if (x == '-')
            cantidadGuiones++;
        if (x == '.')
            cantidadPuntos++;
    }

    if (cantidadGuiones > 1 || cantidadGuiones > 1)
        return false;
    if (cadena[i] == '-')
        i++;
    if (!isdigit(cadena[i]))
        return false;

    return true;
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
string currentDateTime()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;
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
void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}
void centrarTexto(string message, int val = 0, bool horizontal = true, bool vertical = true, int offsetx = 0, int offsety = 0)
{
    int x = (XSIZECMD - size(message)) / 2;
    int y = YSIZECMD / 2;
    if (horizontal && vertical)
    {
        gotoxy(x + offsetx, y + offsety);
        cout << message;
    }
    else if (horizontal)
    {
        gotoxy(x + offsetx, val);
        cout << message;
    }
    else if (vertical)
    {
        gotoxy(val, y + offsety);
        cout << message;
    }
    else
    {
        gotoxy(val, val);
        cout << message;
    }
}
void alinearXTexto(string message, int y, bool izquierda = true, int offsetx = 0, int offsety = 0, bool centradoy = false)
{
    int valy;
    int sizeMessage = size(message);
    if (centradoy)
        valy = (YSIZECMD / 2) + offsety;
    else
        valy = y;

    if (izquierda)
    {
        gotoxy(offsetx, valy);
        cout << message;
    }
    else
    {
        gotoxy(XSIZECMD - offsetx - sizeMessage, valy);
        cout << "   " << message;
    }
}
void dibujarCuadro()
{
    for (int i = 0; i < XSIZECMD - 1; i++)
    {
        string decorador = "-";
        gotoxy(i + 1, 1);
        cout << decorador;
        gotoxy(i + 1, YSIZECMD);
        cout << decorador;
    }
    for (int i = 0; i < YSIZECMD - 1; i++)
    {
        string decorador = "|";
        gotoxy(1, i + 1);
        cout << decorador;
        gotoxy(XSIZECMD - 1, i + 1);
        cout << decorador;
    }
    // cout << endl
    //      << endl;
}
void esquinarTexto(string message, int border = 0, bool up = false, bool left = true, bool print = true)
{
    int x;
    int y;
    if (left)
        x = border + 1;
    else
        x = XSIZECMD - 1 - size(message);
    if (up)
        y = border + 1;
    else
        y = YSIZECMD - border;

    gotoxy(x, y);
    if (print)
        cout << message;
}
void menuListado(vector<string> messages, int separation = 0, string title = "", bool pausar = true)
{
    int sizeY = size(messages) + (size(messages) * separation) / 2 - 1;
    int e = 0;
    system("cls");
    dibujarCuadro();
    if (title != "")
    {
        sizeY += 2 + separation / 2;
        centrarTexto(title, 0, true, true, 0, (-sizeY + e));
        e += 2 + separation;
    }
    for (string x : messages)
    {
        centrarTexto(x, 0, true, true, 0, (-sizeY + e));
        e += 1 + separation;
    }
    if (pausar)
    {
        esquinarTexto("", 1, false, true, false);
        system("pause");
    }
}
void menuError(vector<string> messages, int separation = 0, string color = "0f", string title = "", bool pausar = false)
{
    system("color 4f");
    menuListado(messages, separation, title, pausar);
    if (!pausar)
        Sleep(1000);
    char inp[] = {'c', 'o', 'l', 'o', 'r', ' ', color[0], color[1], '\0'};
    system(inp);
}
void menuDatos(vector<string> messages, vector<string> &answers, int quantCensor = 0, int separation = 0, string title = "")
{
    int sizeY = size(messages) + (size(messages) * separation) / 2 - 1;
    int e = 0, f;
    system("cls");
    dibujarCuadro();
    if (title != "")
    {
        sizeY += 2 + separation / 2;
        centrarTexto(title, 0, true, true, 0, (-sizeY + e));
        e += 2 + separation;
    }
    f = e;
    for (string x : messages)
    {
        alinearXTexto(x + ": ", 0, true, 30, (-sizeY + e), true);
        e += separation + 1;
    }
    e = f;
    int val = messages.size() - quantCensor;
    for (int i = 0; i < messages.size(); i++)
    {
        string answ;
        alinearXTexto(">_ ", 0, false, 65, (-sizeY + e), true);
        if (i < val)
            getline(cin, answ);
        else
            answ = enterContrasena();
        e += separation + 1;
        answers.push_back(answ);
    }
}
bool menuConfirmar(string message, string message2 = " ")
{
    system("cls");
    dibujarCuadro();
    int sizeY = 3;
    int e = 0;
    string opt;
    centrarTexto("¿" + message + "? " + message2 + ". (Confirmar: S/s)", 0, true, true, 0, -3);
    e += 2;
    centrarTexto(">_ ", 0, true, true, -5, 0);
    cin >> opt;
    if (aMinuscula(opt) == "s" || aMinuscula(opt) == "y" || aMinuscula(opt) == "si" || aMinuscula(opt) == "yes")
        return true;
    else
        return false;
}
int menu(string title, vector<string> options)
{
    int sizeY = size(options) + 5 - 1;
    int e = 0, opcionMayor = 0, salida = 0;
    string opc;

    do
    {
        system("cls");
        int e = 0, opcionMayor = 0;
        dibujarCuadro();
        centrarTexto("____" + title + "_____", 0, true, true, 0, (-sizeY + e));
        e++;
        e++;
        for (int i = 0; i < size(options); i++)
        {
            alinearXTexto(options[i], 0, true, 45, (-sizeY + e), true);
            alinearXTexto("[" + to_string(i + 1) + "]", 0, false, 45, (-sizeY + e), true);
            e++;
            opcionMayor = i + 1;
        }
        alinearXTexto("Salir", 0, true, 45, (-sizeY + e), true);
        alinearXTexto("[0]", 0, false, 45, (-sizeY + e), true);
        e++;
        centrarTexto(">_ ", 0, true, true, -2, (-sizeY + e));
        cin >> opc;

        if (esNumero(opc))
        {
            if (stoi(opc) < 0 || stoi(opc) > opcionMayor)
            {
                vector<string> messages = {"~[[INTRODUZCA UNA OPCION VALIDA]]~"};
                menuError(messages);
                opc = "-1";
            }
            else
                salida = stoi(opc);
        }
        else
        {
            vector<string> messages = {"~[[INTRODUZCA UNA OPCION VALIDA]]~"};
            menuError(messages);
            opc = "-1";
        }
    } while (stoi(opc) < 0);
    cin.ignore();
    return salida;
}

#endif