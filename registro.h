#ifndef REGISTRO_H
#define REGISTRO_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class Registro;
}

class Registro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = 0);
    ~Registro();
    bool logins;
    QString *user;

private slots:
    void on_registro_clicked();

    void on_password_returnPressed();

    void on_login_clicked();

    void on_registro2_clicked();

    void on_password2_returnPressed();

private:
    Ui::Registro *ui;

    QMessageBox *msg;

};

#endif // REGISTRO_H
