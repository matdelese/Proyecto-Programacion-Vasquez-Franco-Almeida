#ifndef LIBRO_H
#define LIBRO_H

#include <QString>

struct Libro
{
    int codigo;
    QString titulo;
    QString autor;
    QString editorial;
    QString categoria;
    int anio;
    QString estado;
    QString estudiante;
    QString fechaPrestamo;
    QString fechaDevolucion;
};

#endif
