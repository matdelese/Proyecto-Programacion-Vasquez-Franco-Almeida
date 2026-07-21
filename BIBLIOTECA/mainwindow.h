#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Libro
{
    QString codigo;
    QString titulo;
    QString autor;
    QString editorial;
    QString categoria;
    QString anio;
    QString estado;
    QString estudiante;
    QString fechaPrestamo;
    QString fechaDevolucion;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAgregar_clicked();

    void on_btnBuscar_clicked();

    void on_btnActualizar_clicked();

    void on_btnEliminar_clicked();

    void on_btnLimpiar_clicked();

private:

    Ui::MainWindow *ui;

    void guardarLibro(Libro libro);
    void mostrarLibros();
    void limpiarCampos();
    void actualizarEstadisticas();
};

#endif
