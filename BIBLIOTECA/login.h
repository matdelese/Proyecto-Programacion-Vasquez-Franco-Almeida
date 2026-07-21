#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class dialog;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnIngresar_clicked();

private:
    Ui::dialog *ui;
};

#endif
