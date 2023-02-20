#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include "../controller/controllers.h"
#include "../model/FuncionesGenerales.h"
#include "../model/models.h"

using namespace std;

programController progController;
usuarioController userController;

ProductoController productoController;
MarcaController marcaController;

CompraController compraController;
CompraDController compraDController;

VentaController ventaController;
VentaDController ventaDController;

CajaController cajaController;
KardexController kardexController;

ClienteController clienteController;
ProveedorController proveedorController;

// Option Menus
void menuLogIn();     // ✅
void menuMain();      // ✅
void menuUser();      // ✅
void menuInventory(); // ✅
void menuRecords();   // ✅
void menuOthers();

// Cuenta y usuario
void doRegistrarse(bool);             // ✅
bool doIniciarSesion(bool, string &); // ✅
void doCerrarSesion();                // ✅
void doModificarPerfil(int);          // ✅

void doCompra();
void doVenta();
void doMovimiento();

void askInventario();
void changeDataInventario();
void doAddProducto();
void doAddMarca();

void askEstadoCaja();
void doConsultarRegistro(int);
void doBuscarRegistro();

long long int doRegistrarTercero(bool, long long int);
void doRegistrarRetiroCaja();

#endif