#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class input_data;
}

class input_data : public QDialog
{
    Q_OBJECT

public:
    explicit input_data(QWidget *parent = nullptr);
    ~input_data();

private slots:

    void wrong_input();
    void on_confirm_button_clicked();

private:
    Ui::input_data *ui;
};

#endif // INPUT_DATA_H
