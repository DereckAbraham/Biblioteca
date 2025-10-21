#include "Usuario.h"
#include <iostream>

Usuario::Usuario() {}
Usuario::Usuario(std::string i, std::string n, std::string c, std::string co, std::string t)
    : id(i), nombre(n), carrera(c), correo(co), telefono(t) {}

std::string Usuario::getId() const { return id; }
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getCarrera() const { return carrera; }
std::string Usuario::getCorreo() const { return correo; }
std::string Usuario::getTelefono() const { return telefono; }

void Usuario::setId(const std::string &id) { this->id = id; }
void Usuario::setNombre(const std::string &n) { nombre = n; }
void Usuario::setCarrera(const std::string &c) { carrera = c; }
void Usuario::setCorreo(const std::string &co) { correo = co; }
void Usuario::setTelefono(const std::string &t) { telefono = t; }

void Usuario::mostrarInformacion() const {
    std::cout << "\n🧑 ID: " << id
              << "\n📛 Nombre: " << nombre
              << "\n🎓 Carrera: " << carrera
              << "\n📧 Correo: " << correo
              << "\n📱 Teléfono: " << telefono << "\n";
}
