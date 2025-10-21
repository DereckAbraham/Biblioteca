#include "Prestamo.h"

Prestamo::Prestamo() : activo(true), multa(0.0) {}

Prestamo::Prestamo(std::string idP, std::string idU, std::string i, std::string fP)
    : idPrestamo(idP), idUsuario(idU), isbn(i), fechaPrestamo(fP),
      fechaDevolucion(""), activo(true), multa(0.0) {}

const std::string& Prestamo::getIdPrestamo() const { return idPrestamo; }
const std::string& Prestamo::getIdUsuario()  const { return idUsuario; }
const std::string& Prestamo::getISBN()       const { return isbn; }
const std::string& Prestamo::getFechaPrestamo()   const { return fechaPrestamo; }
const std::string& Prestamo::getFechaDevolucion() const { return fechaDevolucion; }
bool   Prestamo::isActivo() const { return activo; }
double Prestamo::getMulta() const { return multa; }

void Prestamo::setFechaDevolucion(const std::string& f) { fechaDevolucion = f; }
void Prestamo::setActivo(bool a)  { activo = a; }
void Prestamo::setMulta(double m) { multa = m; }
