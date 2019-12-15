#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <QDebug>
#include "input_data.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _enter_amount_of_elements();
}

void MainWindow::Set_number_of_users(int number)
{
    _number_of_users=number;
}

void MainWindow::Set_number_of_errors(int number)
{
    _number_of_errors=number;
}

void MainWindow::Set_number_of_programs(int number)
{
    _number_of_programs=number;
}

void MainWindow::Set_hours_of_work(int number)
{
    _hours_of_work=number;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_enter_amount_of_elements()
{
    ui->centralwidget->setEnabled(false);
    input_data * dialog = new input_data(this);
    dialog->show();
}

void MainWindow::_generate_errors()
{

}

void MainWindow::_generate_users()
{

}

void MainWindow::_generate_programs()
{

}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<_number_of_users;
    qDebug()<<_number_of_programs;
    qDebug()<<_number_of_errors;
    qDebug()<<_hours_of_work;

}
