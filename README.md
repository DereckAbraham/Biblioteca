Introducción
El Sistema de Biblioteca es una aplicación creada para gestionar libros, usuarios y préstamos dentro
de una biblioteca. Permite registrar, actualizar, eliminar y consultar información de forma sencilla,
además de generar reportes y exportar toda la información a un archivo de texto.
Objetivo del sistema
El objetivo principal del sistema es facilitar la administración de la información bibliotecaria mediante un
entorno digital fácil de usar, eficiente y confiable.
Requisitos del sistema
• Sistema operativo: Ubuntu o Windows
• Compilador: g++ compatible con C++17
• Permisos: lectura y escritura para generar archivos TXT en el escritorio.
Instrucciones de instalación
1. Guardar todos los archivos en una carpeta.
2. Abrir la terminal en esa carpeta.
3. Compilar con: g++ -std=c++17 main.cpp Libro.cpp Usuario.cpp Prestamo.cpp SistemaBiblioteca.cpp
-o biblioteca
4. Ejecutar el programa con: ./biblioteca
Menú principal
El menú principal muestra las siguientes opciones:
1) Gestión de Libros
2) Gestión de Usuarios
3) Gestión de Préstamos
4) Reportes y Estadísticas
5) Generar archivo TXT
0) Salir
Módulo de Libros
Permite registrar, listar, actualizar o eliminar libros. Cada libro contiene un ISBN, título, autor, año,
categoría y cantidad disponible.
Módulo de Usuarios
Permite registrar, listar, actualizar, eliminar o buscar usuarios. Cada usuario tiene un ID, nombre,
carrera, correo y teléfono.
Módulo de Préstamos
Permite realizar préstamos, registrar devoluciones, listar préstamos activos y consultar el historial por
usuario. Calcula automáticamente las multas (Q5 por día después de 7 días).
Reportes y Estadísticas
Genera automáticamente los siguientes reportes:
• Libros más prestados (Top 5)
• Usuarios con más préstamos (Top 5)
• Libros ordenados por disponibilidad.
Generar archivo TXT
El sistema genera un archivo de texto con toda la información del sistema y lo guarda
automáticamente en el escritorio del usuario, ya sea en 'Escritorio' o 'Desktop'.
Reglas del sistema
• Un usuario puede tener máximo 3 préstamos activos.
• Un libro no puede prestarse si no hay ejemplares disponibles.
• Las multas se aplican después de 7 días de préstamo (Q5 por día extra).
• Las fechas deben estar en formato DD/MM/AAAA.
Salida del sistema
Cuando el usuario elige la opción 0, el sistema muestra un mensaje de despedida y finaliza
correctamente.
Conclusión
El Sistema de Biblioteca facilita la gestión de libros, usuarios y préstamos, permitiendo mantener un
control completo y generar reportes automáticos de manera eficiente
