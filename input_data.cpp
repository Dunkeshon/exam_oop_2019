#include "input_data.h"
#include "ui_input_data.h"
#include <QVariant>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

input_data::input_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::input_data)
{
    ui->setupUi(this);
}

input_data::~input_data()
{
    delete ui;
}

void input_data::wrong_input()
{
    QMessageBox::StandardButton Btn = QMessageBox::warning(this,"wrong input","Wrong input.Try again",
                                                           QMessageBox::Ok);
     if (Btn == QMessageBox::Yes) {
         on_confirm_button_clicked();
     }
}

void input_data::on_confirm_button_clicked()
{
    bool ok[4];
    MainWindow * temp = qobject_cast <MainWindow *>(parent());
    int worker = ui->workers_edit->text().toInt(&ok[0]);
    int program= ui->programs_edit->text().toInt(&ok[1]);
    int error=ui->errors_edit->text().toInt(&ok[2]);
    int time=ui->hours_edit->text().toInt(&ok[3]);
    if(ok[0] &&ok[1]&&ok[2]&& ok[3])
    {
        if(worker>14||worker<5){
            wrong_input();
        }
        else if(error>14||error<5){
            wrong_input();
        }
        else if(program>14||program<5){
            wrong_input();
        }
        else{
            temp->Set_number_of_users(worker);
            temp->Set_number_of_programs(program);
            temp->Set_number_of_errors(error);
            temp->Set_hours_of_work(time);
            temp->centralWidget()->setEnabled(true);
            hide();
        }
    }
    else{
      wrong_input();
    }
}
