#include "SistemaBiblioteca.h"
#include <iostream>
#include <limits>
#include <cstdlib>   // getenv, system (opcional)
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>
#include <filesystem> // C++17

using namespace std;
namespace fs = std::filesystem;

// ===== Helpers de tabla para MENÚS =====
static void sep(const vector<int>& W, char ch='-') { for (int w : W) cout << '+' << string(w, ch); cout << "+\n"; }
static void row(const vector<string>& cols, const vector<int>& W) {
    for (size_t i = 0; i < W.size(); ++i) cout << "| " << left << setw(W[i]-1) << (i < cols.size() ? cols[i] : "");
    cout << "|\n";
}
static int menuTabla(const string& titulo, const vector<pair<string,string>>& opciones) {
    vector<int> W = {6, 44};
    cout << "\n"; sep(W, '='); row({ "Opción", titulo }, W); sep(W, '=');
    for (auto& op : opciones) row({ op.first, op.second }, W);
    sep(W, '-'); cout << "Seleccione una opción: ";
    int opt;
    if (!(cin >> opt)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada inválida.\n"; return -1; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); return opt;
}

// Asegura extensión .txt
static string ensureTxtExtension(string name) {
    while (!name.empty() && (name.back()==' ' || name.back()=='\t')) name.pop_back();
    while (!name.empty() && (name.front()==' ' || name.front()=='\t')) name.erase(name.begin());
    if (name.empty()) return "reporte_biblioteca.txt";
    if (name.size() >= 4) {
        string suf = name.substr(name.size()-4);
        for (auto &c : suf) c = tolower(c);
        if (suf == ".txt") return name;
    }
    return name + ".txt";
}

// Devuelve la ruta al Escritorio del usuario.
// - Si existe ~/Escritorio lo usa.
// - Si no, usa ~/Desktop.
// - Si ninguno existe, crea ~/Desktop.
// - Siempre termina con '/'.
static std::string detectarEscritorioAuto() {
    const char* home = std::getenv("HOME");
    fs::path base = home ? fs::path(home) : fs::current_path();

    fs::path es = base / "Escritorio";
    fs::path en = base / "Desktop";

    // 1) Preferir "Escritorio" si existe
    if (fs::exists(es) && fs::is_directory(es)) {
        return (es.string() + "/");
    }
    // 2) Si no, "Desktop" si existe
    if (fs::exists(en) && fs::is_directory(en)) {
        return (en.string() + "/");
    }
    // 3) Si ninguno existe, crear "Desktop"
    std::error_code ec;
    if (!fs::exists(en)) {
        fs::create_directories(en, ec);
    }
    // Si la creación falló, usar el directorio actual como último recurso
    if (ec) {
        return (fs::current_path().string() + "/");
    }
    return (en.string() + "/");
}

// ===== Submenús =====
static void menuUsuarios(SistemaBiblioteca &sistema) {
    int opcion;
    do {
        opcion = menuTabla("MENÚ USUARIOS", {
            {"1", "Registrar usuario"},
            {"2", "Listar usuarios"},
            {"3", "Actualizar usuario"},
            {"4", "Eliminar usuario"},
            {"5", "Buscar usuario"},
            {"0", "Volver"}
        });
        switch(opcion) {
            case 1: sistema.registrarUsuario(); break;
            case 2: sistema.listarUsuarios(); break;
            case 3: sistema.actualizarUsuario(); break;
            case 4: sistema.eliminarUsuario(); break;
            case 5: sistema.buscarUsuario(); break;
            case 0: break;
            case -1: default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);
}
static void menuLibros(SistemaBiblioteca &sistema) {
    int opcion;
    do {
        opcion = menuTabla("MENÚ LIBROS", {
            {"1", "Registrar libro"},
            {"2", "Listar libros"},
            {"3", "Actualizar libro"},
            {"4", "Eliminar libro"},
            {"0", "Volver"}
        });
        switch(opcion) {
            case 1: sistema.registrarLibro(); break;
            case 2: sistema.listarLibros(); break;
            case 3: sistema.actualizarLibro(); break;
            case 4: sistema.eliminarLibro(); break;
            case 0: break;
            case -1: default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);
}
static void menuPrestamos(SistemaBiblioteca &sistema) {
    int opcion;
    do {
        opcion = menuTabla("MENÚ PRÉSTAMOS", {
            {"1", "Realizar préstamo"},
            {"2", "Registrar devolución"},
            {"3", "Listar préstamos activos"},
            {"4", "Historial por usuario"},
            {"0", "Volver"}
        });
        switch(opcion) {
            case 1: sistema.realizarPrestamo(); break;
            case 2: sistema.registrarDevolucion(); break;
            case 3: sistema.listarPrestamosActivos(); break;
            case 4: sistema.historialPrestamosPorUsuario(); break;
            case 0: break;
            case -1: default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);
}
static void menuReportes(SistemaBiblioteca &sistema) {
    int opcion;
    do {
        opcion = menuTabla("REPORTES Y ESTADÍSTICAS", {
            {"1", "Libros más prestados (Top 5)"},
            {"2", "Usuarios con más préstamos (Top 5)"},
            {"3", "Top por disponibilidad (todos los libros)"},
            {"0", "Volver"}
        });
        switch(opcion) {
            case 1: sistema.reporteLibrosMasPrestados(); break;
            case 2: sistema.reporteUsuariosConMasPrestamos(); break;
            case 3: sistema.reporteLibrosBajaDisponibilidad(); break;
            case 0: break;
            case -1: default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);
}

// ===== Menú principal =====
int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    SistemaBiblioteca sistema;

    int opcion;
    do {
        opcion = menuTabla("SISTEMA DE BIBLIOTECA", {
            {"1", "Gestión de Libros"},
            {"2", "Gestión de Usuarios"},
            {"3", "Gestión de Préstamos"},
            {"4", "Reportes y Estadísticas"},
            {"5", "Generar TXT (todo) → Escritorio"},
            {"0", "Salir"}
        });

        switch(opcion) {
            case 1: menuLibros(sistema); break;
            case 2: menuUsuarios(sistema); break;
            case 3: menuPrestamos(sistema); break;
            case 4: menuReportes(sistema); break;
            case 5: {
                cout << "Ingrese el nombre del archivo (sin ruta, ej. reporte_final): ";
                string nombre;
                getline(cin, nombre);
                nombre = ensureTxtExtension(nombre);

                // Detectar Escritorio automáticamente (Escritorio/Desktop)
                string escritorio = detectarEscritorioAuto();
                string rutaCompleta = escritorio + nombre;

                cout << "Guardando en: " << rutaCompleta << endl;
                sistema.exportarResumenTXT(rutaCompleta);
                cout << "✅ Archivo generado." << endl;

                // (Opcional) abrir automáticamente el archivo generado:
                // std::string cmd = "xdg-open \"" + rutaCompleta + "\" &";
                // system(cmd.c_str());
                break;
            }
            case 0: cout << "Saliendo del sistema...\n"; break;
            case -1: default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);

    return 0;
}


  /* 
CREATE BY: D2007
.-'--`-._
'-O---O--'
*/

