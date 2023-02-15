#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include "../controller/controllers.h"
#include "../model/FuncionesGenerales.h"

using namespace std;

usuarioController userController;
programController progController;
ProductoController productoController;
MarcaController marcaController;

// Option Menus
void menuLogIn();     // ✅
void menuMain();      // ✅
void menuUser();      // ✅
void menuInventory(); // ✅
void menuRecords();   // ✅

// Cuenta y usuario
void doRegistrarse(bool);               // ✅
bool doIniciarSesion(bool, string &);   // ✅
void doCerrarSesion();                  // ✅
void doModificarPerfil(int);         // ✅

void doAddInventario();
void askInventario();
void changeDataInventario();
void doAddProducto();
void doAddMarca();

#endif