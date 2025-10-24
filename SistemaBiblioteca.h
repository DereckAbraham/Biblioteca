#ifndef SISTEMA_BIBLIOTECA_H
#define SISTEMA_BIBLIOTECA_H

#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"
#include <vector>
#include <string>

class SistemaBiblioteca {
private:
    std::vector<Libro> libros;
    std::vector<Usuario> usuarios;
    std::vector<Prestamo> prestamos;

    // Búsquedas internas
    int buscarLibroPorISBN(const std::string& isbn) const;
    int buscarUsuarioPorID(const std::string& id) const;
    int buscarPrestamoActivoPorId(const std::string& idPrestamo) const;

public:
    // ===== Libros =====
    void registrarLibro();
    void listarLibros();
    void actualizarLibro();
    void eliminarLibro();

    // ===== Usuarios =====
    void registrarUsuario();
    void listarUsuarios();
    void actualizarUsuario();
    void eliminarUsuario();
    void buscarUsuario();

    // ===== Préstamos =====
    void realizarPrestamo();            // pide fecha préstamo (valida)
    void registrarDevolucion();         // pide fecha devolución (valida y calcula multa)
    void listarPrestamosActivos();
    void historialPrestamosPorUsuario();

    // ===== Reportes y Estadísticas =====
    void reporteLibrosMasPrestados(int topN = 5);           // Top 5 fijo
    void reporteUsuariosConMasPrestamos(int topN = 5);      // Top 5 fijo
    void reporteLibrosBajaDisponibilidad(int umbral = 2);   // Top por disponibilidad (todos)

    // ===== Exportar todo a TXT =====
    void exportarResumenTXT(const std::string& filename = "reporte_biblioteca.txt");
};

#endif
  /* 
CREATE BY: D2007
.-'--`-._
'-O---O--'
*/