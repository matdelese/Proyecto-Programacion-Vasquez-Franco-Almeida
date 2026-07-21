#include "login.h"
#include "ui_login.h"

#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialog)
{
    ui->setupUi(this);

    ui->lblTitulo->setStyleSheet(
        "font-size:22px;"
        "font-weight:bold;"
        "color:#1e40af;"
        );


    setWindowTitle("Sistema de Biblioteca");
    setFixedSize(450,300);

    ui->lblTitulo->setText("SISTEMA DE BIBLIOTECA");

    ui->lblTitulo->setAlignment(Qt::AlignCenter);

    ui->lblTitulo->setStyleSheet(
        "font-size:20px;"
        "font-weight:bold;"
        "color:#2c3e50;"
        );

    setStyleSheet(
        "QDialog{"
        "background-color:#f5f7fa;"
        "}"

        "QLineEdit{"
        "border:2px solid #3498db;"
        "border-radius:8px;"
        "padding:5px;"
        "}"

        "QPushButton{"
        "background-color:#3498db;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:8px;"
        "padding:6px;"
        "}"

        "QPushButton:hover{"
        "background-color:#2980b9;"
        "}"
        );

    setWindowTitle("Inicio de Sesión");
    setFixedSize(450, 300);

    setStyleSheet(R"(
        QDialog {
            background-color: #f5f7fa;
        }

        QLabel {
            color: #2c3e50;
            font-size: 11pt;
            font-weight: bold;
        }

        QLineEdit {
            border: 2px solid #3498db;
            border-radius: 8px;
            padding: 6px;
            font-size: 11pt;
            background: white;
        }

        QLineEdit:focus {
            border: 2px solid #2ecc71;
        }

        QPushButton {
            background-color: #3498db;
            color: white;
            border-radius: 10px;
            padding: 8px;
            font-size: 11pt;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #2980b9;
        }

        QPushButton:pressed {
            background-color: #1f6391;
        }
    )");

    setWindowTitle("Sistema de Biblioteca");
    setFixedSize(500,350);

    setStyleSheet(
        "QDialog{"
        "background-color:#f5f7fa;"
        "}"

        "QLabel{"
        "font-size:11pt;"
        "font-weight:bold;"
        "color:#2c3e50;"
        "}"

        "QLineEdit{"
        "border:2px solid #3498db;"
        "border-radius:8px;"
        "padding:6px;"
        "background:white;"
        "}"

        "QLineEdit:focus{"
        "border:2px solid #2ecc71;"
        "}"

        "QPushButton{"
        "background:#3498db;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:10px;"
        "padding:8px;"
        "min-width:120px;"
        "}"

        "QPushButton:hover{"
        "background:#2980b9;"
        "}"
        );
}

Login::~Login()
{
    delete ui;
}


void Login::on_btnIngresar_clicked()
{
    QString usuario = ui->txtUsuario->text().trimmed();
    QString clave = ui->txtPassword->text().trimmed();

    // Validar usuario vacío
    if(usuario.isEmpty())
    {
        QMessageBox::warning(this,
                             "Campo requerido",
                             "Ingrese el usuario.");
        ui->txtUsuario->setFocus();
        return;
    }

    // Validar contraseña vacía
    if(clave.isEmpty())
    {
        QMessageBox::warning(this,
                             "Campo requerido",
                             "Ingrese la contraseña.");
        ui->txtPassword->setFocus();
        return;
    }

    // Validar credenciales
    if(usuario == "admin" && clave == "1234")
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,
                             "Acceso denegado",
                             "Usuario o contraseña incorrectos.");

        ui->txtPassword->clear();
        ui->txtPassword->setFocus();
    }
}



