#include "Libro.h"
#include <iostream>

Libro::Libro() {}
Libro::Libro(std::string i, std::string t, std::string a, int an, std::string c, int cant)
    : isbn(i), titulo(t), autor(a), anio(an), categoria(c), cantidad(cant) {}

std::string Libro::getISBN() const { return isbn; }
std::string Libro::getTitulo() const { return titulo; }
std::string Libro::getAutor() const { return autor; }
int Libro::getAnio() const { return anio; }
std::string Libro::getCategoria() const { return categoria; }
int Libro::getCantidad() const { return cantidad; }

void Libro::setISBN(const std::string &i) { isbn = i; }
void Libro::setTitulo(const std::string &t) { titulo = t; }
void Libro::setAutor(const std::string &a) { autor = a; }
void Libro::setAnio(int an) { anio = an; }
void Libro::setCategoria(const std::string &c) { categoria = c; }
void Libro::setCantidad(int cant) { cantidad = cant; }

void Libro::mostrarInformacion() const {
    std::cout << "\n📘 Título: " << titulo
              << "\n✍️  Autor: " << autor
              << "\n🔢 ISBN: " << isbn
              << "\n📅 Año: " << anio
              << "\n📂 Categoría: " << categoria
              << "\n📦 Cantidad: " << cantidad << "\n";
}
