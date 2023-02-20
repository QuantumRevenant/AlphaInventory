#include <iostream>
#include <Windows.h>
#include <locale.h>
#include <string>
#include "../controller/controllers.h"
#include "../model/FuncionesGenerales.h"
#include "../model/models.h"

using namespace std;

KardexController kardexController;

using namespace std;

int main()
{
    cout<<kardexController.getCantidadProducto(0);
}