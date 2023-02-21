#include <iostream>
#include <Windows.h>
#include <locale.h>
#include <string>
#include "../controller/controllers.h"
#include "../model/FuncionesGenerales.h"
#include "../model/models.h"

using namespace std;

ProductoController productoController;
KardexController kardexController;

#define XSIZECMD 120
#define YSIZECMD 30

int main()
{
    int cod=0;

    int x,y;
    system("cls");
    dibujarCuadro();
    esquinarTexto(" >Producto: "+productoController.get(cod).getNombre(),1,true);

    vector<kardex> movimientos=kardexController.getMovimientosProducto(cod);
    vector<kardex> movimientosMostrar=movimientos;

    for(int j=1;j<XSIZECMD;j++)
    {
        for(int k=1;k<=YSIZECMD;k++)
        {
            gotoxy(j,k);
            if((j==13))
                cout<<"|";
        }
    }

    for(int i=0;i<movimientosMostrar.size();i++)
    {


    }
    esquinarTexto("",1);
    system("pause");

}