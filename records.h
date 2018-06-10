#ifndef RECORDS_H
#define RECORDS_H

#include <QMainWindow>

namespace Ui {
class Records;
}

class Records : public QMainWindow
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = 0);
    ~Records();
    bool open=true;

private slots:

    void on_Salir_clicked();

private:
    Ui::Records *ui;
    QString *record[300][2];

};

#endif // RECORDS_H
