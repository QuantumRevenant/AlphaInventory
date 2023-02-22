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

void showKardex(int cod)
{
    bool menorIgualMax = false;

    int x, y;
    int iterador = 0;
    int movesQuant = 0;
    int intAcum = 0;
    system("cls");
    dibujarCuadro();
    esquinarTexto(" >Producto: " + productoController.get(cod).getNombre(), 1, true);
    esquinarTexto(">Precio: S/." + to_string(productoController.get(cod).getPrecioUnitario()).substr(0,to_string(productoController.get(cod).getPrecioUnitario()).size()-4)+"  ", 1, true,false);

    vector<kardex> movimientos = kardexController.getMovimientosProducto(cod);
    vector<kardex> movimientosMostrar;
    string temporal;
    if (movimientos.size() <= 10)
    {
        movimientosMostrar = movimientos;
        menorIgualMax = true;
    }
    else
    {
        kardex obj = movimientos[0];
        movimientosMostrar.push_back(obj);
        for (int i = 9; i > 0; i--)
        {

            int cantidad = movimientos.size();
            cantidad -= i;
            movimientosMostrar.push_back(movimientos[cantidad]);
        }
        menorIgualMax = false;
    }

    vector<string> NumMovimientos, Fechas, Comprobantes, Entradas, Salidas, Acumulados;
    if (menorIgualMax)
    {
        for (int i = 0; i < movimientosMostrar.size(); i++)
        {
            NumMovimientos.push_back(to_string(movimientosMostrar.size() - i));
            Fechas.push_back(movimientosMostrar[i].getFechaDeEmision());

            if (movimientosMostrar[i].getComprobante().size() > 20)
                temporal = movimientosMostrar[i].getComprobante().substr(0, 17) + "...";
            else
                temporal = movimientosMostrar[i].getComprobante();
            Comprobantes.push_back(temporal);

            if (movimientosMostrar[i].getIsSalida())
            {
                Entradas.push_back("");
                Salidas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                intAcum -= movimientosMostrar[i].getCantidad();
            }
            else
            {
                Entradas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                Salidas.push_back("");
                intAcum += movimientosMostrar[i].getCantidad();
            }
            Acumulados.push_back(to_string(intAcum));
            movesQuant = i + 1;
        }
    }
    else
    {
        NumMovimientos.push_back(to_string(movimientosMostrar.size()));
        Fechas.push_back(movimientosMostrar[0].getFechaDeEmision());
        if (movimientosMostrar[0].getComprobante().size() > 20)
            temporal = movimientosMostrar[0].getComprobante().substr(0, 17) + "...";
        else
            temporal = movimientosMostrar[0].getComprobante();
        Comprobantes.push_back(temporal);

        if (movimientosMostrar[0].getIsSalida())
        {
            Entradas.push_back("");
            Salidas.push_back(to_string(movimientosMostrar[0].getCantidad()));
            intAcum -= movimientosMostrar[0].getCantidad();
        }
        else
        {
            Entradas.push_back(to_string(movimientosMostrar[0].getCantidad()));
            Salidas.push_back("");
            intAcum += movimientosMostrar[0].getCantidad();
        }
        Acumulados.push_back(to_string(intAcum));

        NumMovimientos.push_back("...");
        Fechas.push_back("...");
        Comprobantes.push_back("...");
        Entradas.push_back("...");
        Salidas.push_back("...");
        Acumulados.push_back("...");

        for (int i = 1; i < movimientosMostrar.size(); i++)
        {
            NumMovimientos.push_back(to_string(movimientosMostrar.size() - i - 1));
            Fechas.push_back(movimientosMostrar[i].getFechaDeEmision());

            if (movimientosMostrar[i].getComprobante().size() > 20)
                temporal = movimientosMostrar[i].getComprobante().substr(0, 17) + "...";
            else
                temporal = movimientosMostrar[i].getComprobante();
            Comprobantes.push_back(temporal);

            if (movimientosMostrar[i].getIsSalida())
            {
                Entradas.push_back("");
                Salidas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                intAcum -= movimientosMostrar[i].getCantidad();
            }
            else
            {
                Entradas.push_back(to_string(movimientosMostrar[i].getCantidad()));
                Salidas.push_back("");
                intAcum += movimientosMostrar[i].getCantidad();
            }
            Acumulados.push_back(to_string(intAcum));
            movesQuant = i + 1;
        }
    }

    for (int j = 1; j < XSIZECMD; j++)
    {
        for (int k = 1; k <= YSIZECMD; k++)
        {
            if (((j > 95 && j < 117) && (k == YSIZECMD - 3)) || ((j > 1 && j < XSIZECMD - 1) && (k == 7)))
                cout << "-";
            gotoxy(j, k);
            if ((j == 13 || j == 26 || j == 49 || j == 72 || j == 95) && ((k < YSIZECMD - 2 && k > 4)))
                cout << "|";
        }
    }

    y = 7;

    gotoxy(4, y - 2);
    cout << "Num Mov:";

    gotoxy(15, y - 2);
    cout << "Fechas:";

    gotoxy(28, y - 2);
    cout << "Comprobante:";

    gotoxy(51, y - 2);
    cout << "ENTRADAS:";

    gotoxy(74, y - 2);
    cout << "SALIDAS:";

    gotoxy(97, y - 2);
    cout << "ACUMULADOS:";
    for (int k = 1; k <= YSIZECMD; k++)
    {

        for (int j = 1; j < XSIZECMD; j++)
        {
            gotoxy(j, k);
            if ((k == y) && y < YSIZECMD - 4)
            {
                if (j == 5)
                    cout << NumMovimientos[iterador];

                if (j == 15)
                {
                    cout << Fechas[iterador];
                }

                if (j == 28)
                    cout << Comprobantes[iterador];

                if (j == 51)
                    cout << Entradas[iterador];

                if (j == 74)
                    cout << Salidas[iterador];

                if (j == 97)
                {
                    cout << Acumulados[iterador];
                    iterador++;
                    y += 2;
                }
            }
            if (iterador == movesQuant)
                break;
        }
        if (iterador == movesQuant)
            break;
    }

    gotoxy(87, YSIZECMD - 3);
    cout << "TOTAL: ";
    gotoxy(97, YSIZECMD - 3);
    cout << Acumulados.back();

    esquinarTexto("", 1);
    system("pause");
}

int main()
{
    showKardex(0);
}