#ifndef MARCACONTROLLER_H
#define MARCACONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Marca.cpp"

class MarcaController
{
private:
    vector<Marca> vectorMarca;

public:
    MarcaController();
    int     getCorrelativo();
    void    add(Marca);
    void    modify(Marca, int);
    int     size();
    Marca   get(int);
    void    saveFile();
    void    copyFile();
};

MarcaController::MarcaController()
{
    copyFile();
}
int     MarcaController::getCorrelativo()
{
	if(size()==0)		
	{
		return 1;	
	}
	else
	{
		return vectorMarca[size() - 1].getCodUsuarioMarca() + 1;
	}
}
void    MarcaController::add(Marca obj)
{
    vectorMarca.push_back(obj);
}
void    MarcaController::modify(Marca temp, int obj)
{
    vectorMarca[obj] = temp;
}
int     MarcaController::size()
{
    return vectorMarca.size();
}
Marca MarcaController::get(int pos)
{
    return vectorMarca[pos];
}
void    MarcaController::saveFile()
{
    try
    {
        fstream archivoMarcas;
        archivoMarcas.open("../data/marcas.csv", ios::out);
        if (archivoMarcas.is_open())
        {
            for (Marca obj:vectorMarca)
            {
                archivoMarcas << obj.getCodUsuarioMarca() << "," << obj.getNombreMarca() << ",";
                archivoMarcas << endl;
            }
            archivoMarcas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
    
}
void    MarcaController::copyFile()
{
    try
    {
        int i;
        size_t posi;
        string linea;
        fstream archivoMarcas;
        archivoMarcas.open("../data/marcas.csv", ios::in);
        if (archivoMarcas.is_open())
        {
            while (!archivoMarcas.eof() && getline(archivoMarcas, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(";")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Marca obj;
                obj.setCodigoMarca(stoi(temporal[0]));
                obj.setNombreMarca(temporal[1]);
                add(obj);
            }
            archivoMarcas.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
    }
    
}
#endif // PRODUCTOCONTROLLER_H