#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include <iostream>

class Libro {
private:
    std::string isbn;
    std::string titulo;
    std::string autor;
    int anio;
    std::string categoria;
    int cantidad;

public:
    Libro();
    Libro(std::string i, std::string t, std::string a, int an, std::string c, int cant);

    // Getters
    std::string getISBN() const;
    std::string getTitulo() const;
    std::string getAutor() const;
    int getAnio() const;
    std::string getCategoria() const;
    int getCantidad() const;

    // Setters
    void setISBN(const std::string &i);
    void setTitulo(const std::string &t);
    void setAutor(const std::string &a);
    void setAnio(int an);
    void setCategoria(const std::string &c);
    void setCantidad(int cant);

    void mostrarInformacion() const;
};

#endif
