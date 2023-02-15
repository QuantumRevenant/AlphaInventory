#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

*/

bool esNumero(std::string &cadena)
{
    bool resultado = true, point = false;
    int i = 0;
    string salida;
    int cantidadGuiones = 0, cantidadPuntos = 0;
    cout<<"Here 1"<<endl;
    if (cadena.size() == 0)
        return false;
    cout<<"Here 2"<<endl;
    if (cadena.size() == 1 && (cadena[0] == '.' || cadena[0] == '-'))
        return false;
    cout<<"Here 3"<<endl;
    for (char x : cadena)
    {
        if (!isdigit(x) && x != '-' && x != '.')
            return false;
        if (x == '-')
            cantidadGuiones++;
        if (x == '.')
            cantidadPuntos++;
    }
    cout<<"Here 4"<<endl;
    cout<<cantidadGuiones<<endl;
    cout<<cantidadPuntos<<endl;
    if (cantidadGuiones > 1 || cantidadGuiones > 1)
        return false;
    cout<<"Here 5"<<endl;
    if (cadena[i] == '-')
        i++;
    cout<<"Here 6"<<endl;
    if (!isdigit(cadena[i]))
        return false;

    return true;
}

int main(int argc, char *argv[])
{
    
    string val;
    do
    {
    system("pause");
    system("cls");
    cin>>val;
    }while(!esNumero(val));
    return 0;
}