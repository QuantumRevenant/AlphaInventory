#include <iostream>
#include <string>
#include <vector>
#include "../controller/usuarioController.h"

// usuarioController userController;

using namespace std;

/*

*/

class test
{
public:
    string nombre;
    test() { nombre = "empty"; }
    test(string _nombre) { nombre = _nombre; }
};

int main(int argc, char const *argv[])
{
    test a("1");
    test b("2");
    vector<test> vec = {a, b};
    test obj2;

    std::ofstream s("file.bin", std::ios::out|std::ios::app | std::ios::binary);
    for (test x : vec)
        s.write((const char *)&x, sizeof(x));
    s.close();
    std::ifstream in("file.bin", std::ios::in | std::ios::binary);
    in.read((char *)&obj2, sizeof(obj2));
    in.close();
    std::cout << obj2.nombre << '\n';

    return 0;
}

// int main(int argc, char *argv[])
// {
// cout << "Here" << endl;
// system("pause");
// userController.archRecuperarDatos();
// cout << "Here" << endl;
// for (int i = 0; i < userController.size(); i++)
//     cout << userController.get(i).getCodUsuario() << endl;
// cout<<userController.size();
// cout << "Here" << endl;
// userController.archGrabarDatos();
// return 0;
// }