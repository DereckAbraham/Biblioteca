#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>

class Prestamo {
private:
    std::string idPrestamo;
    std::string idUsuario;
    std::string isbn;
    std::string fechaPrestamo;    // "DD/MM/YYYY"
    std::string fechaDevolucion;  // "" si no devuelto
    bool activo;
    double multa;

public:
    Prestamo();
    Prestamo(std::string idP, std::string idU, std::string i, std::string fP);

    // Getters
    const std::string& getIdPrestamo() const;
    const std::string& getIdUsuario() const;
    const std::string& getISBN() const;
    const std::string& getFechaPrestamo() const;
    const std::string& getFechaDevolucion() const;
    bool   isActivo() const;
    double getMulta() const;

    // Setters
    void setFechaDevolucion(const std::string& f);
    void setActivo(bool a);
    void setMulta(double m);
};

#endif
  /* 
CREATE BY: D2007
.-'--`-._
'-O---O--'
*/