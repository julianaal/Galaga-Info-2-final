#include "menu.h"
#include "ui_menu.h"
#include <qdebug.h>


Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    msg= new QMessageBox();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_exit_clicked()
{
    this->close();
}

void Menu::on_help_clicked()
{
    msg->setWindowTitle("****Bienvenido A Galaga****");
    msg->setText("\nDestruye naves espaciales.\n Disparale a las naves para eliminarlas. \n Mueve a la derecha: tecla D.\n Mueve a la izquierda: tecla A.\n Mueve arriba: tecla W.\n Mueve abajo: tecla S.\n Dispara: tecla Control");
    msg->show();
}

void Menu::on_logout_clicked()
{
    logout=true;
}

void Menu::on_one_clicked()
{

    single=true;
}

void Menu::on_multi_clicked()
{
    multi=true;
}

void Menu::on_pushButton_clicked()
{
    record=true;
}
