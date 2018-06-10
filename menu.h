#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QMessageBox>
#include "widget.h"


namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    bool logout=true;
    bool single=false;
    bool multi=false;
    bool cerrar=false;
    bool record=false;

private slots:
    void on_exit_clicked();

    void on_help_clicked();

    void on_logout_clicked();

    void on_one_clicked();

    void on_multi_clicked();

    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
    QMessageBox *msg;


};

#endif // MENU_H
