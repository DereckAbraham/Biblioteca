#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

class Usuario {
private:
    std::string id;
    std::string nombre;
    std::string carrera;
    std::string correo;
    std::string telefono;

public:
    Usuario();
    Usuario(std::string i, std::string n, std::string c, std::string co, std::string t);

    // Getters
    std::string getId() const;
    std::string getNombre() const;
    std::string getCarrera() const;
    std::string getCorreo() const;
    std::string getTelefono() const;

    // Setters
    void setId(const std::string &id);
    void setNombre(const std::string &n);
    void setCarrera(const std::string &c);
    void setCorreo(const std::string &co);
    void setTelefono(const std::string &t);

    void mostrarInformacion() const;
};

#endif
  /* 
CREATE BY: D2007
.-'--`-._
'-O---O--'
*/