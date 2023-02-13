#ifndef PRODUCTOCONTROLLER_H
#define PRODUCTOCONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../model/Producto.cpp"

class ProductoController
{
private:
    vector<Producto> vectorProducto;

public:
    ProductoController();
    void        add(Producto);
    int         getCorrelativo();
    void        modify(Producto, int);
    int         size();
    Producto    get(int);
    bool        nombreRegistrado(string);
    void        saveFile();
    void        copyFile();
};

ProductoController::ProductoController()
{
    copyFile();
}
int     ProductoController::getCorrelativo()
{
	if(size()==0)		
	{
		return 1;	
	}
	else
	{
		return vectorProducto[size() - 1].getCodigo() + 1;
	}
}
void    ProductoController::add(Producto obj)
{
    vectorProducto.push_back(obj);
}
void    ProductoController::modify(Producto temp, int obj)
{
    vectorProducto[obj] = temp;
}
int     ProductoController::size()
{
    return vectorProducto.size();
}
Producto ProductoController::get(int pos)
{
    return vectorProducto[pos];
}
bool    ProductoController::nombreRegistrado(string _nombre)
{
    for(Producto x:vectorProducto)
    {
        if (aMayuscula(x.getNombre()) == aMayuscula(_nombre))
        {
            return true;
        }else
        {
            return false;
        }
    }
}
void    ProductoController::saveFile()
{
    try
    {
        fstream archivoProductos;
        archivoProductos.open("../data/productos.csv", ios::out);
        if (archivoProductos.is_open())
        {
            for (Producto obj:vectorProducto)
            {
                archivoProductos << obj.getCodigo() << ","
                                 << obj.getNombre() << ","
                                 << obj.getNumMarcas() << ",";
                for (int i = 0; i < obj.getNumMarcas(); i++)
                    archivoProductos << obj.getMarca(i).getCodigoMarca() << ","
                                     << obj.getMarca(i).getNombreMarca() << ","
                                     << obj.getPrecioUnitario(i) << ","
                                     << obj.getStock(i) << ",";
                archivoProductos << obj.getNumComponentes() << ",";
                for (int i = 0; i < obj.getNumComponentes(); i++)
                    archivoProductos << obj.getComponente(i).getNombre() << ","
                                     << obj.getComponente(i).getCantidad() << ",";
                archivoProductos << endl;
            }
            archivoProductos.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al momento de grabar en el archivo";
    }
    
}
void    ProductoController::copyFile()
{
    try
    {
        int i;
        int j;
        size_t posi;
        string linea;
        fstream archivoProductos;
        archivoProductos.open("../data/productos.csv", ios::in);
        if (archivoProductos.is_open())
        {
            while (!archivoProductos.eof() && getline(archivoProductos, linea))
            {
                vector<string> temporal;
                i = 0;
                while ((posi = linea.find(",")) != string::npos)
                {
                    temporal.push_back(linea.substr(0, posi));
                    linea.erase(0, posi + 1);
                    i++;
                }
                Producto obj;
                obj.setCodigo(stoi(temporal[0]));
                obj.setNombre(temporal[1]);
                obj.setNumMarcas(stoi(temporal[2]));
                j = 3;
                for (int k = 0; k < obj.getNumMarcas(); k++)
                {
                    Marca marca;
                    marca.setCodigoMarca(stoi(temporal[j]));
                    marca.setNombreMarca(temporal[j + 1]);
                    obj.addMarca(marca, stof(temporal[j + 2]));
                    obj.modifyStock(stoi(temporal[j + 3]), k);
                    j = j + 4;
                }
                obj.setNumComponentes(stoi(temporal[j]));
                j++;
                for (int k = 0; k < obj.getNumComponentes(); k++)
                {
                    Componente comp;
                    comp.setNombre(temporal[j]);
                    comp.setCantidad(temporal[j + 1]);
                    obj.addComponente(comp);
                    j = j + 2;
                }
                add(obj);
            }
            archivoProductos.close();
        }
    }
    catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo";
        system("pause");
    }
    
}
#endif // PRODUCTOCONTROLLER_H
