#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Cliente.cpp"

class ClienteController
{
private:
    vector<Cliente> vectorCliente;

public:
    ClienteController();
    int     getCorrelativo();
    void    add(Cliente);
    void    modify(Cliente, int);
    int     size();
    Cliente get(int);
    int getPosDoc(long long int,string);
    void    saveFile();
    void    copyFile();
};

ClienteController::ClienteController()
{
    copyFile();
}
int     ClienteController::getCorrelativo()
{
	if(size()==0)		
	{
		return 1;	
	}
	else
	{
		return vectorCliente[size() - 1].getCodCliente() + 1;
	}
}
void    ClienteController::add(Cliente obj)
{
    vectorCliente.push_back(obj);
}
void    ClienteController::modify(Cliente temp, int obj)
{
    vectorCliente[obj] = temp;
}
int     ClienteController::size()
{
    return vectorCliente.size();
}
Cliente ClienteController::get(int pos)
{
    return vectorCliente[pos];
}
int ClienteController::getPosDoc(long long int Doc,string typeDoc)
{
    for (Cliente x : vectorCliente)
    {
        if(x.getDocumento()==Doc&&x.getTipoDocumento()==typeDoc)
            return x.getCodCliente();
    }
    return -1;
}
void    ClienteController::saveFile()
{
    try
    {
        fstream archivoClientes;
        archivoClientes.open("../data/clientes.csv", ios::app);
        if (archivoClientes.is_open())
        {
            
            Cliente obj = vectorCliente.back();
                archivoClientes << obj.getCodCliente() << ","
                                << obj.getNombre() << ","
                                << obj.getTipoDocumento() << ","
                                << obj.getDocumento() << ",";
                archivoClientes << endl;
            
            archivoClientes.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
}
void    ClienteController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoClientes;
        vectorCliente.clear();
        archivoClientes.open("../data/clientes.csv", ios::in);
        if (archivoClientes.is_open())
        {
            while (!archivoClientes.eof() && getline(archivoClientes, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Cliente obj;
                obj.setCodCliente(stoi(temporal[0]));
                obj.setNombre(temporal[1]);
                obj.setTipoDocumento(temporal[2]);
                obj.setDocumento(stoll(temporal[3]));
                add(obj);
            }
            archivoClientes.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
}
#endif // CLIENTECONTROLLER_H