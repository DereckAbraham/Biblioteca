#include "SistemaBiblioteca.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <limits>
#include <vector>
#include <fstream>
#include <regex>
#include <cctype>

using namespace std;

// ========================= Helpers de IMPRESIÓN (TABLAS) =========================
static void printSep(const vector<int>& W, char ch='-') {
    for (int w : W) { cout << '+' << string(w, ch); }
    cout << "+\n";
}
static void printRow(const vector<string>& cols, const vector<int>& W) {
    for (size_t i = 0; i < W.size(); ++i) {
        cout << "| " << left << setw(W[i]-1) << (i < cols.size() ? cols[i] : "");
    }
    cout << "|\n";
}
static string boolStr(bool v) { return v ? "Sí" : "No"; }

// ========================= Helpers de FECHA =========================
static tm parseDate(const string& ddmmyyyy) {
    tm t{}; t.tm_isdst = -1;
    if (ddmmyyyy.size() == 10 && ddmmyyyy[2]=='/' && ddmmyyyy[5]=='/') {
        t.tm_mday = stoi(ddmmyyyy.substr(0,2));
        t.tm_mon  = stoi(ddmmyyyy.substr(3,2)) - 1;
        t.tm_year = stoi(ddmmyyyy.substr(6,4)) - 1900;
    }
    return t;
}
static long daysBetween(const string& d1, const string& d2) {
    tm t1 = parseDate(d1);
    tm t2 = parseDate(d2);
    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);
    const long seconds_per_day = 60*60*24;
    return static_cast<long>((time2 - time1) / seconds_per_day);
}
static double calcularMultaPrestamo(const string& fPrestamo, const string& fDevolucion) {
    long dias = daysBetween(fPrestamo, fDevolucion);
    long extra = dias - 7;
    return (extra > 0) ? (extra * 5.0) : 0.0;
}

// ======================= LIBROS =======================
void SistemaBiblioteca::registrarLibro() {
    string isbn = "ISBN-" + to_string(100000 + rand() % 900000);
    string titulo, autor, categoria;
    int anio, cantidad;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n--- Registro de Libro ---\n";
    cout << "Título: "; getline(cin, titulo);
    cout << "Autor: "; getline(cin, autor);
    cout << "Año: "; cin >> anio; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Categoría: "; getline(cin, categoria);
    cout << "Cantidad disponible: "; cin >> cantidad; cin.ignore(numeric_limits<streamsize>::max(), '\n');

    libros.push_back(Libro(isbn, titulo, autor, anio, categoria, cantidad));
    cout << "\n✅ Libro \"" << titulo << "\" (ISBN: " << isbn << ") registrado correctamente.\n";
}

void SistemaBiblioteca::listarLibros() {
    if (libros.empty()) { cout << "No hay libros registrados.\n"; return; }

    vector<int> W = {14, 28, 22, 8, 16, 10};
    printSep(W);
    printRow({"ISBN","Título","Autor","Año","Categoría","Cant."}, W);
    printSep(W,'=');
    for (auto &l : libros)
        printRow({l.getISBN(), l.getTitulo(), l.getAutor(),
                  to_string(l.getAnio()), l.getCategoria(),
                  to_string(l.getCantidad())}, W);
    printSep(W);
}

void SistemaBiblioteca::actualizarLibro() {
    string isbn;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese ISBN del libro a actualizar: "; getline(cin, isbn);

    for (auto &l : libros) {
        if (l.getISBN() == isbn) {
            string titulo, autor, categoria; int anio, cantidad;
            cout << "Nuevo título: "; getline(cin, titulo);
            cout << "Nuevo autor: "; getline(cin, autor);
            cout << "Nuevo año: "; cin >> anio; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nueva categoría: "; getline(cin, categoria);
            cout << "Nueva cantidad: "; cin >> cantidad; cin.ignore(numeric_limits<streamsize>::max(), '\n');

            l.setTitulo(titulo); l.setAutor(autor);
            l.setAnio(anio); l.setCategoria(categoria);
            l.setCantidad(cantidad);

            vector<int> W = {14, 28, 22, 8, 16, 10};
            printSep(W);
            printRow({"ISBN","Título","Autor","Año","Categoría","Cant."}, W);
            printSep(W,'=');
            printRow({ l.getISBN(), l.getTitulo(), l.getAutor(),
                       to_string(l.getAnio()), l.getCategoria(), to_string(l.getCantidad()) }, W);
            printSep(W);
            cout << "✅ Libro actualizado.\n";
            return;
        }
    }
    cout << "Libro no encontrado.\n";
}

void SistemaBiblioteca::eliminarLibro() {
    string isbn; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese ISBN del libro a eliminar: "; getline(cin, isbn);

    auto it = remove_if(libros.begin(), libros.end(),
        [&](const Libro &l){ return l.getISBN() == isbn; });
    if (it != libros.end()) {
        libros.erase(it, libros.end());
        cout << "✅ Libro eliminado.\n";
    } else cout << "Libro no encontrado.\n";
}

// ======================= USUARIOS =======================
void SistemaBiblioteca::registrarUsuario() {
    string id = "USR-" + to_string(10000 + rand() % 90000);
    string nombre, carrera, correo, telefono;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n--- Registro de Usuario ---\n";
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Carrera: "; getline(cin, carrera);
    cout << "Correo: "; getline(cin, correo);
    cout << "Teléfono: "; getline(cin, telefono);

    usuarios.push_back(Usuario(id, nombre, carrera, correo, telefono));
    cout << "\n✅ Usuario \"" << nombre << "\" (ID: " << id << ") registrado correctamente.\n";
}

void SistemaBiblioteca::listarUsuarios() {
    if (usuarios.empty()) { cout << "No hay usuarios registrados.\n"; return; }

    vector<int> W = {12, 22, 18, 28, 14};
    printSep(W);
    printRow({"ID","Nombre","Carrera","Correo","Teléfono"}, W);
    printSep(W,'=');
    for (auto &u : usuarios)
        printRow({u.getId(), u.getNombre(), u.getCarrera(),
                  u.getCorreo(), u.getTelefono()}, W);
    printSep(W);
}

void SistemaBiblioteca::buscarUsuario() {
    string criterio; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese ID o nombre: "; getline(cin, criterio);

    vector<int> W = {12, 22, 18, 28, 14}; 
    bool found = false;

    for (auto &u : usuarios) {
        if (u.getId() == criterio || u.getNombre() == criterio) {
            if (!found) {
                printSep(W);
                printRow({"ID","Nombre","Carrera","Correo","Teléfono"}, W);
                printSep(W,'=');
            }
            found = true;
            printRow({ u.getId(), u.getNombre(), u.getCarrera(), u.getCorreo(), u.getTelefono() }, W);
        }
    }
    if (found) printSep(W); 
    else cout << "Usuario no encontrado.\n";
}

void SistemaBiblioteca::actualizarUsuario() {
    string id; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese ID del usuario a actualizar: "; getline(cin, id);

    for (auto &u : usuarios) {
        if (u.getId() == id) {
            string nombre, carrera, correo, telefono;
            cout << "Nuevo nombre: "; getline(cin, nombre);
            cout << "Nueva carrera: "; getline(cin, carrera);
            cout << "Nuevo correo: "; getline(cin, correo);
            cout << "Nuevo teléfono: "; getline(cin, telefono);

            u.setNombre(nombre); u.setCarrera(carrera);
            u.setCorreo(correo); u.setTelefono(telefono);
            cout << "✅ Usuario actualizado.\n";
            return;
        }
    }
    cout << "Usuario no encontrado.\n";
}

void SistemaBiblioteca::eliminarUsuario() {
    string id; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese ID del usuario a eliminar: "; getline(cin, id);

    auto it = remove_if(usuarios.begin(), usuarios.end(),
        [&](const Usuario &u){ return u.getId() == id; });
    if (it != usuarios.end()) {
        usuarios.erase(it, usuarios.end());
        cout << "✅ Usuario eliminado.\n";
    } else cout << "Usuario no encontrado.\n";
}

// ======================= BÚSQUEDAS INTERNAS =======================
int SistemaBiblioteca::buscarLibroPorISBN(const string& isbn) const {
    for (size_t i = 0; i < libros.size(); ++i)
        if (libros[i].getISBN() == isbn) return static_cast<int>(i);
    return -1;
}
int SistemaBiblioteca::buscarUsuarioPorID(const string& id) const {
    for (size_t i = 0; i < usuarios.size(); ++i)
        if (usuarios[i].getId() == id) return static_cast<int>(i);
    return -1;
}
int SistemaBiblioteca::buscarPrestamoActivoPorId(const string& idPrestamo) const {
    for (size_t i = 0; i < prestamos.size(); ++i)
        if (prestamos[i].getIdPrestamo() == idPrestamo && prestamos[i].isActivo()) return static_cast<int>(i);
    return -1;
}

// ======================= PRÉSTAMOS =======================
void SistemaBiblioteca::realizarPrestamo() {
    string idUsuario, isbn, fechaPrestamo;
    cout << "\n--- Realizar Préstamo ---\n";
    cout << "ID de Usuario: "; getline(cin, idUsuario);
    cout << "ISBN del Libro: "; getline(cin, isbn);
    cout << "Fecha de préstamo (DD/MM/YYYY): "; getline(cin, fechaPrestamo);

    int iu = buscarUsuarioPorID(idUsuario);  if (iu == -1) { cout << "❌ Usuario no encontrado.\n"; return; }
    int il = buscarLibroPorISBN(isbn);       if (il == -1) { cout << "❌ Libro no encontrado.\n"; return; }
    if (libros[il].getCantidad() <= 0) { cout << "❌ No hay ejemplares disponibles.\n"; return; }

    // Límite de 3 préstamos activos por usuario
    int activos = 0;
    for (const auto& p : prestamos) if (p.getIdUsuario()==idUsuario && p.isActivo()) activos++;
    if (activos >= 3) { cout << "❌ Límite de 3 préstamos activos alcanzado.\n"; return; }

    string idPrestamo = "PRE-" + to_string(10000 + rand() % 90000);
    prestamos.push_back(Prestamo(idPrestamo, idUsuario, isbn, fechaPrestamo));
    libros[il].setCantidad(libros[il].getCantidad() - 1);

    vector<int> W1 = {14, 16, 12};
    printSep(W1);
    printRow({"ID Préstamo","Fecha Préstamo","Estado"}, W1);
    printSep(W1,'=');
    printRow({idPrestamo, fechaPrestamo, "Activo"}, W1);
    printSep(W1);

    vector<int> WU = {12, 22, 18, 28, 14};
    printSep(WU);
    printRow({"ID","Nombre","Carrera","Correo","Teléfono"}, WU);
    printSep(WU,'=');
    printRow({ usuarios[iu].getId(), usuarios[iu].getNombre(), usuarios[iu].getCarrera(),
               usuarios[iu].getCorreo(), usuarios[iu].getTelefono() }, WU);
    printSep(WU);

    vector<int> WL = {14, 28, 22, 8, 16};
    printSep(WL);
    printRow({"ISBN","Título","Autor","Año","Categoría"}, WL);
    printSep(WL,'=');
    printRow({ libros[il].getISBN(), libros[il].getTitulo(), libros[il].getAutor(),
               to_string(libros[il].getAnio()), libros[il].getCategoria() }, WL);
    printSep(WL);
}

void SistemaBiblioteca::registrarDevolucion() {
    cout << "\n--- Registrar Devolución ---\n";
    cout << "ID de Préstamo: ";
    string idP; getline(cin, idP);

    int ip = buscarPrestamoActivoPorId(idP);
    if (ip == -1) { cout << "❌ Préstamo activo no encontrado.\n"; return; }

    cout << "Fecha de devolución (DD/MM/YYYY): ";
    string fechaDev; getline(cin, fechaDev);

    prestamos[ip].setFechaDevolucion(fechaDev);
    prestamos[ip].setActivo(false);

    int il = buscarLibroPorISBN(prestamos[ip].getISBN());
    if (il != -1) { libros[il].setCantidad(libros[il].getCantidad() + 1); }

    double multa = calcularMultaPrestamo(prestamos[ip].getFechaPrestamo(), fechaDev);
    prestamos[ip].setMulta(multa);

    vector<int> W1 = {14, 16, 16, 10};
    printSep(W1);
    printRow({"ID Préstamo","Prestado","Devuelto","Activo"}, W1);
    printSep(W1,'=');
    printRow({ prestamos[ip].getIdPrestamo(), prestamos[ip].getFechaPrestamo(),
               prestamos[ip].getFechaDevolucion(), boolStr(prestamos[ip].isActivo()) }, W1);
    printSep(W1);

    vector<int> WM = {24};
    printSep(WM);
    ostringstream ms; ms << "Multa: Q" << fixed << setprecision(2) << multa;
    printRow({ ms.str() }, WM);
    printSep(WM);

    if (il != -1) {
        vector<int> WL = {14, 28, 22};
        printSep(WL);
        printRow({"ISBN","Título","Autor"}, WL);
        printSep(WL,'=');
        printRow({ libros[il].getISBN(), libros[il].getTitulo(), libros[il].getAutor() }, WL);
        printSep(WL);
    }
}

void SistemaBiblioteca::listarPrestamosActivos() {
    cout << "\n--- Préstamos Activos ---\n";
    vector<int> W = {14, 16, 12, 14, 22, 8, 28};
    printSep(W);
    printRow({"ID Préstamo","Fecha","ID Usuario","ISBN","Nombre Usuario","Año","Título Libro"}, W);
    printSep(W,'=');

    bool vacio = true;
    for (const auto& p : prestamos) {
        if (!p.isActivo()) continue;
        vacio = false;

        int iu = buscarUsuarioPorID(p.getIdUsuario());
        int il = buscarLibroPorISBN(p.getISBN());

        string nombreU = (iu != -1) ? usuarios[iu].getNombre() : "[no encontrado]";
        string anioL   = (il != -1) ? to_string(libros[il].getAnio()) : "-";
        string tituloL = (il != -1) ? libros[il].getTitulo() : "[no encontrado]";

        printRow({ p.getIdPrestamo(), p.getFechaPrestamo(), p.getIdUsuario(), p.getISBN(),
                   nombreU, anioL, tituloL }, W);
    }
    printSep(W);
    if (vacio) cout << "No hay préstamos activos.\n";
}

void SistemaBiblioteca::historialPrestamosPorUsuario() {
    cout << "\n--- Historial por Usuario ---\n";
    cout << "ID de Usuario: ";
    string idU; getline(cin, idU);

    int iu = buscarUsuarioPorID(idU);

    if (iu != -1) {
        vector<int> WU = {12, 22, 18, 28, 14};
        printSep(WU);
        printRow({"ID","Nombre","Carrera","Correo","Teléfono"}, WU);
        printSep(WU,'=');
        printRow({ usuarios[iu].getId(), usuarios[iu].getNombre(), usuarios[iu].getCarrera(),
                   usuarios[iu].getCorreo(), usuarios[iu].getTelefono() }, WU);
        printSep(WU);
    } else {
        cout << "Usuario no encontrado (se mostrará historial si existiera).\n";
    }

    vector<int> W = {14, 14, 28, 16, 16, 8, 10};
    printSep(W);
    printRow({"ID Préstamo","ISBN","Título","Prestado","Devuelto","Activo","Multa"}, W);
    printSep(W,'=');

    bool encontrado = false;
    for (const auto& p : prestamos) {
        if (p.getIdUsuario() != idU) continue;
        encontrado = true;

        int il = buscarLibroPorISBN(p.getISBN());
        string tituloL = (il != -1) ? libros[il].getTitulo() : "[no encontrado]";

        ostringstream multaFmt; multaFmt << "Q" << fixed << setprecision(2) << p.getMulta();
        printRow({ p.getIdPrestamo(), p.getISBN(), tituloL,
                   p.getFechaPrestamo(),
                   (p.getFechaDevolucion().empty() ? "-" : p.getFechaDevolucion()),
                   boolStr(p.isActivo()),
                   multaFmt.str() }, W);
    }
    printSep(W);
    if (!encontrado) cout << "Sin préstamos para ese usuario.\n";
}

// ======================= REPORTES =======================
void SistemaBiblioteca::reporteLibrosBajaDisponibilidad(int /*umbral*/) {
    cout << "\n=== Reporte: Top de Libros por Disponibilidad (mayor → menor) ===\n";

    if (libros.empty()) {
        cout << "No hay libros en el catálogo.\n";
        return;
    }

    vector<int> idx(libros.size());
    for (size_t i = 0; i < libros.size(); ++i) idx[i] = static_cast<int>(i);
    sort(idx.begin(), idx.end(), [&](int a, int b){
        if (libros[a].getCantidad() != libros[b].getCantidad())
            return libros[a].getCantidad() > libros[b].getCantidad();
        return libros[a].getTitulo() < libros[b].getTitulo();
    });

    vector<int> W = {10, 14, 28, 22, 8, 16, 10};
    printSep(W);
    printRow({"RANK","ISBN","Título","Autor","Año","Categoría","Cant."}, W);
    printSep(W,'=');

    const int N = static_cast<int>(idx.size());
    for (int i = 0; i < N; ++i) {
        const auto& L = libros[idx[i]];
        string r = to_string(i + 1);
        if (i == 0) r += " (mejor)";
        if (i == N - 1) r += " (peor)";

        printRow({
            r, L.getISBN(), L.getTitulo(), L.getAutor(),
            to_string(L.getAnio()), L.getCategoria(),
            to_string(L.getCantidad())
        }, W);
    }
    printSep(W);
}

void SistemaBiblioteca::reporteLibrosMasPrestados(int /*topN*/) {
    cout << "\n=== Reporte: Libros más prestados (Top 5) ===\n";

    unordered_map<string, int> freq;
    for (const auto& p : prestamos) { freq[p.getISBN()]++; }
    if (freq.empty()) { cout << "No hay registros de préstamos.\n"; return; }

    vector<pair<string,int>> items(freq.begin(), freq.end());
    sort(items.begin(), items.end(), [](auto& a, auto& b){
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    vector<int> W = {10, 14, 28, 22, 8, 16, 10};
    printSep(W);
    printRow({"RANK","ISBN","Título","Autor","Año","Categoría","Préstamos"}, W);
    printSep(W,'=');

    int toShow = static_cast<int>(min<size_t>(5, items.size()));
    for (int i = 0; i < toShow; ++i) {
        const auto& kv = items[i];
        const string& isbn = kv.first;
        int prestamosCount = kv.second;

        string r = to_string(i + 1);
        if (i == 0) r += " (mejor)";
        if (i == toShow - 1) r += " (peor)";

        int il = buscarLibroPorISBN(isbn);
        if (il != -1) {
            const auto& L = libros[il];
            printRow({ r, L.getISBN(), L.getTitulo(), L.getAutor(),
                       to_string(L.getAnio()), L.getCategoria(),
                       to_string(prestamosCount) }, W);
        } else {
            printRow({ r, isbn, "[no en catálogo]", "-", "-", "-", to_string(prestamosCount) }, W);
        }
    }
    printSep(W);
}

void SistemaBiblioteca::reporteUsuariosConMasPrestamos(int /*topN*/) {
    cout << "\n=== Reporte: Usuarios con más préstamos (Top 5) ===\n";

    unordered_map<string, int> freq;
    for (const auto& p : prestamos) { freq[p.getIdUsuario()]++; }
    if (freq.empty()) { cout << "No hay registros de préstamos.\n"; return; }

    vector<pair<string,int>> items(freq.begin(), freq.end());
    sort(items.begin(), items.end(), [](auto& a, auto& b){
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    vector<int> W = {10, 12, 22, 18, 28, 14, 10};
    printSep(W);
    printRow({"RANK","ID","Nombre","Carrera","Correo","Teléfono","Préstamos"}, W);
    printSep(W,'=');

    int toShow = static_cast<int>(min<size_t>(5, items.size()));
    for (int i = 0; i < toShow; ++i) {
        const auto& kv = items[i];
        const string& idU = kv.first;
        int prestamosCount = kv.second;

        string r = to_string(i + 1);
        if (i == 0) r += " (mejor)";
        if (i == toShow - 1) r += " (peor)";

        int iu = buscarUsuarioPorID(idU);
        if (iu != -1) {
            const auto& U = usuarios[iu];
            printRow({ r, U.getId(), U.getNombre(), U.getCarrera(),
                       U.getCorreo(), U.getTelefono(),
                       to_string(prestamosCount) }, W);
        } else {
            printRow({ r, idU, "[no encontrado]", "-", "-", "-", to_string(prestamosCount) }, W);
        }
    }
    printSep(W);
}

// ======================= EXPORTAR TODO A TXT =======================
void SistemaBiblioteca::exportarResumenTXT(const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "❌ No se pudo abrir el archivo: " << filename << "\n";
        return;
    }

    auto line = [&](char ch='=', int n=80){ out << string(n, ch) << "\n"; };

    out << "SISTEMA DE BIBLIOTECA - REPORTE COMPLETO\n";
    line('=');

    // ---- Libros
    out << "\n[LIBROS REGISTRADOS]\n";
    line('-');
    if (libros.empty()) out << "(Sin libros)\n";
    else {
        out << left << setw(16) << "ISBN"
                     << setw(30) << "Titulo"
                     << setw(22) << "Autor"
                     << setw(6)  << "Anio"
                     << setw(16) << "Categoria"
                     << setw(8)  << "Cant" << "\n";
        line('-');
        for (const auto& L : libros) {
            out << left << setw(16) << L.getISBN()
                        << setw(30) << L.getTitulo()
                        << setw(22) << L.getAutor()
                        << setw(6)  << L.getAnio()
                        << setw(16) << L.getCategoria()
                        << setw(8)  << L.getCantidad() << "\n";
        }
    }

    // ---- Usuarios
    out << "\n[USUARIOS REGISTRADOS]\n";
    line('-');
    if (usuarios.empty()) out << "(Sin usuarios)\n";
    else {
        out << left << setw(12) << "ID"
                     << setw(22) << "Nombre"
                     << setw(18) << "Carrera"
                     << setw(28) << "Correo"
                     << setw(14) << "Telefono" << "\n";
        line('-');
        for (const auto& U : usuarios) {
            out << left << setw(12) << U.getId()
                        << setw(22) << U.getNombre()
                        << setw(18) << U.getCarrera()
                        << setw(28) << U.getCorreo()
                        << setw(14) << U.getTelefono() << "\n";
        }
    }

    // ---- Prestamos (todos)
    out << "\n[PRESTAMOS]\n";
    line('-');
    if (prestamos.empty()) out << "(Sin prestamos)\n";
    else {
        out << left << setw(14) << "ID_Prestamo"
                     << setw(12) << "ID_User"
                     << setw(14) << "ISBN"
                     << setw(12) << "Prestado"
                     << setw(12) << "Devuelto"
                     << setw(8)  << "Activo"
                     << setw(8)  << "Multa" << "\n";
        line('-');

        ostringstream multaFmt;
        for (const auto& P : prestamos) {
            multaFmt.str(""); multaFmt.clear();
            multaFmt << fixed << setprecision(2) << P.getMulta();

            out << left << setw(14) << P.getIdPrestamo()
                        << setw(12) << P.getIdUsuario()
                        << setw(14) << P.getISBN()
                        << setw(12) << P.getFechaPrestamo()
                        << setw(12) << (P.getFechaDevolucion().empty() ? "-" : P.getFechaDevolucion())
                        << setw(8)  << (P.isActivo() ? "Si" : "No")
                        << setw(8)  << multaFmt.str() << "\n";
        }
    }

    // ---- Estadísticas
    out << "\n[ESTADISTICAS]\n";
    line('-');

    // Top 5 Libros más prestados
    {
        unordered_map<string,int> freq;
        for (const auto& p : prestamos) freq[p.getISBN()]++;

        out << "\n- Top 5 Libros mas prestados:\n";
        if (freq.empty()) out << "(Sin datos de prestamos)\n";
        else {
            vector<pair<string,int>> items(freq.begin(), freq.end());
            sort(items.begin(), items.end(), [](auto&a, auto&b){
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });
            int toShow = static_cast<int>(min<size_t>(5, items.size()));
            out << left << setw(6)  << "Rank"
                        << setw(16) << "ISBN"
                        << setw(30) << "Titulo"
                        << setw(22) << "Autor"
                        << setw(6)  << "Anio"
                        << setw(16) << "Categoria"
                        << setw(10) << "Prestamos" << "\n";
            line('-');
            for (int i=0;i<toShow;++i) {
                const string& isbn = items[i].first;
                int count = items[i].second;
                int il = buscarLibroPorISBN(isbn);
                string titulo="-", autor="-", categoria="-"; int anio=0;
                if (il!=-1){ titulo=libros[il].getTitulo(); autor=libros[il].getAutor(); categoria=libros[il].getCategoria(); anio=libros[il].getAnio(); }
                string rank = to_string(i+1);
                if (i==0) rank += " (mejor)";
                if (i==toShow-1) rank += " (peor)";
                out << left << setw(6)  << rank
                            << setw(16) << isbn
                            << setw(30) << titulo
                            << setw(22) << autor
                            << setw(6)  << anio
                            << setw(16) << categoria
                            << setw(10) << count << "\n";
            }
        }
    }

    // Top 5 Usuarios con más préstamos
    {
        unordered_map<string,int> freq;
        for (const auto& p : prestamos) freq[p.getIdUsuario()]++;

        out << "\n- Top 5 Usuarios con mas prestamos:\n";
        if (freq.empty()) out << "(Sin datos de prestamos)\n";
        else {
            vector<pair<string,int>> items(freq.begin(), freq.end());
            sort(items.begin(), items.end(), [](auto&a, auto&b){
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });
            int toShow = static_cast<int>(min<size_t>(5, items.size()));
            out << left << setw(6)  << "Rank"
                        << setw(12) << "ID"
                        << setw(22) << "Nombre"
                        << setw(18) << "Carrera"
                        << setw(28) << "Correo"
                        << setw(14) << "Telefono"
                        << setw(10) << "Prestamos" << "\n";
            line('-');
            for (int i=0;i<toShow;++i) {
                const string& idU = items[i].first;
                int count = items[i].second;
                int iu = buscarUsuarioPorID(idU);
                string nombre="-", carrera="-", correo="-", telefono="-";
                if (iu!=-1){ nombre=usuarios[iu].getNombre(); carrera=usuarios[iu].getCarrera(); correo=usuarios[iu].getCorreo(); telefono=usuarios[iu].getTelefono(); }
                string rank = to_string(i+1);
                if (i==0) rank += " (mejor)";
                if (i==toShow-1) rank += " (peor)";
                out << left << setw(6)  << rank
                            << setw(12) << idU
                            << setw(22) << nombre
                            << setw(18) << carrera
                            << setw(28) << correo
                            << setw(14) << telefono
                            << setw(10) << count << "\n";
            }
        }
    }

    // Top por disponibilidad (todos)
    {
        out << "\n- Top por disponibilidad (mayor -> menor):\n";
        if (libros.empty()) out << "(Sin libros)\n";
        else {
            vector<int> idx(libros.size());
            for (size_t i=0;i<libros.size();++i) idx[i]=static_cast<int>(i);
            sort(idx.begin(), idx.end(), [&](int a, int b){
                if (libros[a].getCantidad() != libros[b].getCantidad())
                    return libros[a].getCantidad() > libros[b].getCantidad();
                return libros[a].getTitulo() < libros[b].getTitulo();
            });
            out << left << setw(6)  << "Rank"
                        << setw(16) << "ISBN"
                        << setw(30) << "Titulo"
                        << setw(22) << "Autor"
                        << setw(6)  << "Anio"
                        << setw(16) << "Categoria"
                        << setw(8)  << "Cant" << "\n";
            line('-');
            for (int i=0; i<(int)idx.size(); ++i) {
                const auto& L = libros[idx[i]];
                string rank = to_string(i+1);
                if (i==0) rank += " (mejor)";
                if (i==(int)idx.size()-1) rank += " (peor)";
                out << left << setw(6)  << rank
                            << setw(16) << L.getISBN()
                            << setw(30) << L.getTitulo()
                            << setw(22) << L.getAutor()
                            << setw(6)  << L.getAnio()
                            << setw(16) << L.getCategoria()
                            << setw(8)  << L.getCantidad() << "\n";
            }
        }
    }

    out << "\n(Fin del reporte)\n";
    out.close();
    cout << "📝 Reporte generado: " << filename << "\n";
}

// ======================= IMPORTAR DESDE TXT (NUEVO) =======================
// Nota: Lectura robusta por secciones. Usa separador de 2+ espacios para columnas.
static inline string trim(const string& s){
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a==string::npos) return "";
    return s.substr(a, b-a+1);
}
static vector<string> splitCols2PlusSpaces(const string& line) {
    // Divide por 2+ espacios consecutivos
    static const regex re(R"(\s{2,})");
    sregex_token_iterator it(line.begin(), line.end(), re, -1), end;
    vector<string> out;
    for (; it != end; ++it) {
        string t = trim(it->str());
        if (!t.empty()) out.push_back(t);
    }
    return out;
}
bool SistemaBiblioteca::cargarDesdeTXT(const string& rutaTXT) {
    ifstream in(rutaTXT);
    if (!in) return false;

    libros.clear();
    usuarios.clear();
    prestamos.clear();

    enum Sec { NONE, LIBROS_SEC, USUARIOS_SEC, PRESTAMOS_SEC, OTHER };
    Sec sec = NONE;

    string line;
    bool headerPassed = false; // para saltar cabeceras y líneas de guiones en cada sección

    auto toLower = [](string s){ for (char &c: s) c = static_cast<char>(tolower(c)); return s; };

    while (std::getline(in, line)) {
        string L = trim(line);
        if (L.empty()) { continue; }

        // Detectar cambio de sección por encabezado entre corchetes
        if (!L.empty() && L.front()=='[' && L.back()==']') {
            headerPassed = false;
            string s = toLower(L);
            if (s.find("libros registrados") != string::npos) sec = LIBROS_SEC;
            else if (s.find("usuarios registrados") != string::npos) sec = USUARIOS_SEC;
            else if (s.find("prestamos") != string::npos) sec = PRESTAMOS_SEC;
            else sec = OTHER;
            continue;
        }

        // Saltar líneas de títulos y de guiones tras entrar a sección
        if (!headerPassed) {
            // buscar una línea de cabecera (nombres de columnas) y la siguiente de guiones "----"
            if (L.find("---") != string::npos) { headerPassed = true; }
            else if (L.find("ISBN") != string::npos) { /* todavía viene línea de guiones */ }
            else if (L.find("ID") != string::npos && sec!=LIBROS_SEC) { /* idem */ }
            else if (L.find("ID_Prestamo") != string::npos) { /* idem */ }
            continue;
        }
        if (L.find("---") != string::npos) continue; // líneas separadoras dentro de sección

        // Procesar filas de datos según sección
        if (sec == LIBROS_SEC) {
            // Esperamos 6 columnas: ISBN, Titulo, Autor, Anio, Categoria, Cant
            auto cols = splitCols2PlusSpaces(L);
            if (cols.size() < 6) continue;
            string isbn = cols[0];
            string titulo = cols[1];
            string autor = cols[2];
            int anio = 0; try { anio = stoi(cols[3]); } catch(...) {}
            string categoria = cols[4];
            int cant = 0; try { cant = stoi(cols[5]); } catch(...) {}
            libros.emplace_back(isbn, titulo, autor, anio, categoria, cant);
        } else if (sec == USUARIOS_SEC) {
            // Esperamos 5 columnas: ID, Nombre, Carrera, Correo, Telefono
            auto cols = splitCols2PlusSpaces(L);
            if (cols.size() < 5) continue;
            usuarios.emplace_back(cols[0], cols[1], cols[2], cols[3], cols[4]);
        } else if (sec == PRESTAMOS_SEC) {
            // Esperamos 7 columnas: ID_Prestamo, ID_User, ISBN, Prestado, Devuelto, Activo, Multa
            auto cols = splitCols2PlusSpaces(L);
            if (cols.size() < 7) continue;
            string idP = cols[0];
            string idU = cols[1];
            string isbn = cols[2];
            string fP  = cols[3];
            string fD  = (cols[4] == "-" ? "" : cols[4]);
            string sActivo = toLower(cols[5]);
            bool activo = (sActivo=="si" || sActivo=="sí" || sActivo=="yes" || sActivo=="true");
            double multa = 0.0; try { multa = stod(cols[6]); } catch(...) {}

            Prestamo p(idP, idU, isbn, fP);
            p.setFechaDevolucion(fD);
            p.setActivo(activo);
            p.setMulta(multa);
            prestamos.push_back(p);

            // IMPORTANTE: ajustar stock del libro en función de préstamos activos
            int il = buscarLibroPorISBN(isbn);
            if (il != -1) {
                // Si el préstamo está activo, significa que ese ejemplar está fuera → restar 1 si hay stock
                if (activo) {
                    int c = libros[il].getCantidad();
                    if (c > 0) libros[il].setCantidad(c - 1);
                } else {
                    // si está devuelto, no tocamos la cantidad (suponemos export ya reflejó stock).
                }
            }
        } else {
            // Secciones ignoradas (estadísticas, etc.)
            continue;
        }
    }

    return true;
}
