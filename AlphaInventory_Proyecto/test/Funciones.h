#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include "../model/FuncionesGenerales.h"

using namespace std;

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
void doModificarPerfil(string);         // ✅

#endif