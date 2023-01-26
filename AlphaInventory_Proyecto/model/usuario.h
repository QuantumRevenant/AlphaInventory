#include "clases.h"

Usuario::Usuario() {}
void Usuario::setUsername(string _username) {
    username = _username;
}
void Usuario::setNombre(string _nombre) {
    nombre = _nombre;
}
void Usuario::setApellidos(string _apellidos) {
    apellidos = _apellidos;
}
void Usuario::setDocumento(string _documento) {
    documento = _documento;
}
void Usuario::setNumDocumento(int _numDocumento) {
    numDocumento = _numDocumento;
}
void Usuario::setContrasena(string _contrasena) {
    contrasena = _contrasena;
}
void Usuario::setTipoUsuario(string _tipoUsuario) {
    tipoUsuario = _tipoUsuario;
}
string  Usuario::getUsername() {
    return username;
}
string  Usuario::getNombre() {
    return nombre;
}
string  Usuario::getApellidos() {
    return apellidos;
}
string  Usuario::getDocumento() {
    return documento;
}
int     Usuario::getNumDocumento() {
    return numDocumento;
}
string  Usuario::getContrasena() {
    return contrasena;
}
string  Usuario::getTipoUsuario() {
    return tipoUsuario;
}