#include <iostream>
#include <string>
#include <vector>
#include "../model/Usuario.cpp"
#include "../model/FuncionesGenerales.h"
using namespace std;

/*

*/

int main(int argc, char *argv[])
{
    // Usuario objUsuario;
    // string test="test";
    // cout<<test<<endl;
    // cout<<objUsuario.encriptar(test)<<endl;
    // cout<<objUsuario.desencriptar(objUsuario.encriptar(test))<<endl;

    string test1="152.5",
            test2="-162.4",
            test3="163art",
            test4="-3agt",
            test5="thx";
    
    esNumero(test1)?cout<<"numero :"<<stoi(test1)<<endl:cout<<"no es numero"<<endl;
    esNumero(test2)?cout<<"numero :"<<stoi(test2)<<endl:cout<<"no es numero"<<endl;
    esNumero(test3)?cout<<"numero :"<<stoi(test3)<<endl:cout<<"no es numero"<<endl;
    esNumero(test4)?cout<<"numero :"<<stoi(test4)<<endl:cout<<"no es numero"<<endl;
    esNumero(test5)?cout<<"numero :"<<stoi(test5)<<endl:cout<<"no es numero"<<endl;

    return 0;
}
