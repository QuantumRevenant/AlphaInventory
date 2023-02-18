#ifndef USUARIOCONTROLLER_H
#define USUARIOCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Usuario.cpp"
#include "../controller/Encrypter/sha256.cpp"

class usuarioController
{
private:
    vector<Usuario> vectorUsuario;

public:
    usuarioController();
    ~usuarioController();

    void add(Usuario);
    int size();
    Usuario get(int);
    void modify(Usuario, int);

    bool validarSesion(string, string); // nos valida si existe una sesión.
    bool existeUsuario(string);
    bool existeUsuario(string, int&);
    bool existeAdministrador();

    int getNewCodUsuario();
    Usuario getUsuario(int);            // nos devuelve el usuario por medio de su key. (censurar la contraseña).
    Usuario getUsuario(string, string); // nos devuelve el usuario por medio de su usuario y contraseña.

    void archGrabarDatos();
    void archRecuperarDatos();
};

usuarioController::usuarioController() { archRecuperarDatos(); }
usuarioController::~usuarioController() {}

void usuarioController::add(Usuario obj) { vectorUsuario.push_back(obj); }
int usuarioController::size() { return vectorUsuario.size(); }
Usuario usuarioController::get(int pos) { return vectorUsuario[pos]; }
void usuarioController::modify(Usuario obj, int pos) { vectorUsuario[pos] = obj; }

bool usuarioController::validarSesion(string username, string contrasena)
{
    int i = 0;
    bool found = false;
    found = existeUsuario(username,i);
    cout<<i<<"  "<<vectorUsuario[i - 1].getCodUsuario()<<endl;
    if (found)
    {
        if (sha256(contrasena) == vectorUsuario[i - 1].getContrasena())
            return true;
        else
            return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
    }
    else
        return false; // "Username y contraseña incorrectos y/o no registrados en nuestra base de datos."
}
bool usuarioController::existeUsuario(string username)
{
    int i = 0;
    bool found = false;
    while (i < (int)vectorUsuario.size() && !found)
    {
        if (aMinuscula(vectorUsuario[i].getUsername()) == aMinuscula(username))
            found = true;
        i++;
    }
    return found;
}
bool usuarioController::existeUsuario(string username,int &e)
{
    int i = 0;
    bool found = false;
    while (i < (int)vectorUsuario.size() && !found)
    {
        if (aMinuscula(vectorUsuario[i].getUsername()) == aMinuscula(username))
            found = true;
        i++;
    }
    e=i;
    return found;
}
bool usuarioController::existeAdministrador()
{
    archRecuperarDatos();
    for(Usuario x:vectorUsuario)
        if(x.getTipoUsuario()=="Administrador")
            return true;
    
    return false;
}

int usuarioController::getNewCodUsuario() { return vectorUsuario.size(); }
Usuario usuarioController::getUsuario(int key)
{
    int i = 0;
    bool found = false;

    while (i < (int)vectorUsuario.size() && !found)
    {
        if (vectorUsuario[i].getCodUsuario() == key)
            found = true;
        i++;
    }
    Usuario objSalida = vectorUsuario[i - 1];
    return objSalida;
}
Usuario usuarioController::getUsuario(string username, string contrasena)
{
    int i = 0;
    bool found = false;
    if (!validarSesion(username, contrasena))
    {
        Usuario objInvalido;
        return objInvalido;
    }
    else
    {
        while (i < (int)vectorUsuario.size() && !found)
        {
            if (vectorUsuario[i].getUsername() == username)
                found = true;
            i++;
        }
        Usuario objSalida = vectorUsuario[i - 1];
        objSalida.setContrasena("********");
        return objSalida;
    }
}

void usuarioController::archGrabarDatos()
{
    try
    {
        fstream archivoUsuarios;
        archivoUsuarios.open("../data/usuarios.csv", ios::out);
        if (archivoUsuarios.is_open())
        {
            for (Usuario obj : vectorUsuario)
            {
                archivoUsuarios << obj.getTipoDocumento() << "," << obj.getNumDocumento() << ","
                                << obj.getUsername() << "," << obj.getContrasena() << ","
                                << obj.getNombre() << "," << obj.getApellidos() << ","
                                << obj.getTipoUsuario() << "," << obj.getCodUsuario() << "," << endl;
            }
        }
        archivoUsuarios.close();
    }
    catch (exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}

void usuarioController::archRecuperarDatos()
{
    int i;
    size_t posi; // Cantidad maxima
    string linea;
    vector<string> temporal; // Cantidad de columnas
    fstream archivoUsuarios;
    archivoUsuarios.open("../data/usuarios.csv", ios::in);
    if (archivoUsuarios.is_open())
    {
        while (!archivoUsuarios.eof() && getline(archivoUsuarios, linea))
        {
            i = 0;
            while ((posi = linea.find(",")) != string::npos)
            {                                        /*string::npos es -1, termina cuando llega a este punto*/
                temporal.push_back(linea.substr(0, posi)); /*posi = Es la cantidad de caracteres antes del ;*/
                linea.erase(0, posi + 1);            // borra la palabra de la primera posici�n encontrada   y con el +1 incluye hasta el ; y luego borra ese elemento, para que en la siguiente iteracion iniciar con la siguiente palabra y de ese modo seguir el proceso ,
                i++;
            }
            // Asignando los valores al vector
            Usuario usuario;
            usuario.setDocumento(temporal[0]);
            usuario.setNumDocumento(stoi(temporal[1]));
            usuario.setUsername(temporal[2]);
            usuario.setContrasena(temporal[3]);
            cout<<temporal[3]<<"   ";
            usuario.setNombre(temporal[4]);
            usuario.setApellidos(temporal[5]);
            usuario.setTipoUsuario(temporal[6]);
            usuario.setCodUsuario(stoi(temporal[7]));
            cout << "Usuario " << temporal[7] << " cargado..." << endl;
            Sleep(1);
            add(usuario);
        }
    }
    archivoUsuarios.close();
}

#endif