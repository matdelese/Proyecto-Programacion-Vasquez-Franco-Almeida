#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDate>

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QFont>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QMainWindow{"
        "border-image:url(:/imagenes/biblioteca.jpg);"
        "}"
        );

    ui->groupBox->setStyleSheet(
        "QGroupBox{"
        "background-color: rgba(255,255,255,150);"
        "}");

    ui->groupBox_2->setStyleSheet(
        "QGroupBox{"
        "background-color: rgba(255,255,255,1   50);"
        "}");

    ui->groupBox->setStyleSheet(
        "QGroupBox{"
        "background-color: rgba(255,255,255,180);"
        "border-radius:10px;"
        "}"
        );

    // Configurar la tabla
    ui->tableWidget->setColumnCount(10);

    QStringList encabezados;

    encabezados << "Código"
                << "Título"
                << "Autor"
                << "Editorial"
                << "Categoría"
                << "Año"
                << "Estado"
                << "Estudiante"
                << "Prestamo"
                << "Devolución";

    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mostrarLibros();

    actualizarEstadisticas();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAgregar_clicked()
{
    Libro libro;

    libro.codigo = ui->txtCodigo->text();
    libro.titulo = ui->txtTitulo->text();
    libro.autor = ui->txtAutor->text();
    libro.editorial = ui->txtEditorial->text();
    libro.categoria = ui->cbCategoria->currentText();
    libro.anio = ui->txtAnio->text();

    if(ui->rbDisponible->isChecked())
        libro.estado = "Disponible";
    else
        libro.estado = "Prestado";

    libro.estudiante = ui->txtEstudiante->text();

    libro.fechaPrestamo = ui->dtPrestamo->date().toString("dd/MM/yyyy");
    libro.fechaDevolucion = ui->dtDevolucion->date().toString("dd/MM/yyyy");

    // Validar campos obligatorios
    if(libro.codigo.isEmpty() ||
        libro.titulo.isEmpty() ||
        libro.autor.isEmpty() ||
        libro.editorial.isEmpty() ||
        libro.anio.isEmpty())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Complete todos los campos obligatorios.");
        return;
    }

    guardarLibro(libro);

    QMessageBox::information(this,
                             "Correcto",
                             "Libro agregado correctamente.");

    mostrarLibros();

    actualizarEstadisticas();

    limpiarCampos();
}





void MainWindow::guardarLibro(Libro libro)
{
    QFile archivo("libros.txt");

    if(archivo.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream salida(&archivo);

        salida
            << libro.codigo << ";"
            << libro.titulo << ";"
            << libro.autor << ";"
            << libro.editorial << ";"
            << libro.categoria << ";"
            << libro.anio << ";"
            << libro.estado << ";"
            << libro.estudiante << ";"
            << libro.fechaPrestamo << ";"
            << libro.fechaDevolucion
            << "\n";

        archivo.close();
    }
}

void MainWindow::limpiarCampos()
{
    ui->txtCodigo->clear();
    ui->txtTitulo->clear();
    ui->txtAutor->clear();
    ui->txtEditorial->clear();
    ui->txtAnio->clear();
    ui->txtEstudiante->clear();

    ui->cbCategoria->setCurrentIndex(0);

    ui->rbDisponible->setChecked(true);

    ui->dtPrestamo->setDate(QDate::currentDate());
    ui->dtDevolucion->setDate(QDate::currentDate());

    ui->txtCodigo->setFocus();
}

void MainWindow::mostrarLibros()
{
    QFile archivo("libros.txt");

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream entrada(&archivo);

    ui->tableWidget->setRowCount(0);

    int fila = 0;

    while(!entrada.atEnd())
    {
        QString linea = entrada.readLine();

        QStringList datos = linea.split(";");

        ui->tableWidget->insertRow(fila);

        for(int i=0; i<datos.size(); i++)
        {
            ui->tableWidget->setItem(fila,
                                     i,
                                     new QTableWidgetItem(datos[i]));
        }

        fila++;
    }

    archivo.close();
}

void MainWindow::actualizarEstadisticas()
{
    QFile archivo("libros.txt");

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream entrada(&archivo);

    int disponibles = 0;
    int prestados = 0;
    int total = 0;

    while(!entrada.atEnd())
    {
        QString linea = entrada.readLine();

        QStringList datos = linea.split(";");

        if(datos.size() >= 7)
        {
            total++;

            if(datos[6] == "Disponible")
                disponibles++;

            if(datos[6] == "Prestado")
                prestados++;
        }
    }

    archivo.close();

    ui->lblDisponibles->setText(QString::number(disponibles));
    ui->lblPrestados->setText(QString::number(prestados));
    ui->lblTotal->setText(QString::number(total));
}


void MainWindow::on_btnBuscar_clicked()
{
    QString codigoBuscado = ui->txtCodigo->text();

    QFile archivo("libros.txt");

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream entrada(&archivo);

    bool encontrado = false;

    while(!entrada.atEnd())
    {
        QString linea = entrada.readLine();
        QStringList datos = linea.split(";");

        if(datos[0] == codigoBuscado)
        {
            ui->txtTitulo->setText(datos[1]);
            ui->txtAutor->setText(datos[2]);
            ui->txtEditorial->setText(datos[3]);
            ui->cbCategoria->setCurrentText(datos[4]);
            ui->txtAnio->setText(datos[5]);

            if(datos[6] == "Disponible")
                ui->rbDisponible->setChecked(true);
            else
                ui->rbPrestado->setChecked(true);

            ui->txtEstudiante->setText(datos[7]);

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if(!encontrado)
    {
        QMessageBox::information(this,
                                 "Buscar",
                                 "Libro no encontrado");
    }
}

void MainWindow::on_btnActualizar_clicked()
{
    QString codigo = ui->txtCodigo->text();

    QFile archivo("libros.txt");

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lineas;
    QTextStream entrada(&archivo);

    while(!entrada.atEnd())
    {
        QString linea = entrada.readLine();

        QStringList datos = linea.split(";");

        if(datos[0] == codigo)
        {
            QString estado;

            if(ui->rbDisponible->isChecked())
                estado = "Disponible";
            else
                estado = "Prestado";

            QString nuevaLinea =
                ui->txtCodigo->text() + ";" +
                ui->txtTitulo->text() + ";" +
                ui->txtAutor->text() + ";" +
                ui->txtEditorial->text() + ";" +
                ui->cbCategoria->currentText() + ";" +
                ui->txtAnio->text() + ";" +
                estado + ";" +
                ui->txtEstudiante->text() + ";" +
                ui->dtPrestamo->date().toString("dd/MM/yyyy") + ";" +
                ui->dtDevolucion->date().toString("dd/MM/yyyy");

            lineas.append(nuevaLinea);
        }
        else
        {
            lineas.append(linea);
        }
    }

    archivo.close();

    if(!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,
                             "Error",
                             "No se pudo abrir el archivo.");
        return;
    }

    QTextStream salida(&archivo);

    for(const QString &linea : lineas)
    {
        salida << linea << "\n";
    }

    archivo.close();

    mostrarLibros();
    actualizarEstadisticas();

    QMessageBox::information(this,
                             "Actualizar",
                             "Libro actualizado correctamente");
}

void MainWindow::on_btnEliminar_clicked()
{
    QString codigo = ui->txtCodigo->text();

    QFile archivo("libros.txt");

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lineas;
    QTextStream entrada(&archivo);

    while(!entrada.atEnd())
    {
        QString linea = entrada.readLine();

        QStringList datos = linea.split(";");

        if(datos[0] != codigo)
            lineas.append(linea);
    }

    archivo.close();

    if(!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,
                             "Error",
                             "No se pudo abrir el archivo.");
        return;
    }

    QTextStream salida(&archivo);

    for(const QString &linea : lineas)
    {
        salida << linea << "\n";
    }

    archivo.close();

    mostrarLibros();
    actualizarEstadisticas();
    limpiarCampos();

    QMessageBox::information(this,
                             "Eliminar",
                             "Libro eliminado correctamente");
}

void MainWindow::on_btnLimpiar_clicked()
{
    limpiarCampos();
}












