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

void MainWindow::generate_data()
{
    _generate_programs();
    _generate_errors();
    _generate_users();
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
    vector<string> common_errors { "Overheating","Brain Lag","Bad input","ecxeption thrown",
                           "No connection", "Empty screen", "pc explosion", "virus",
                           "Lags", "slow responce" , " Wrong password","Wrong ID",
                           "Wrong key", "Server problems"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(common_errors.begin(),common_errors.end(),gen); // shuffle
    common_errors.erase(common_errors.begin() + _number_of_errors, common_errors.end());// resize
    for(const auto &i:common_errors){
        errors.push_back(error(i,programs));
    }
}

void MainWindow::_generate_users()
{
    vector<string> common_users {"Anatoliy", "Andrii","Artur", "Vlad","Dima","Danil",
                                 "German","Isaac" "Max","Roman", "Pavel", "Thomas","Ted",
                                 "Zack"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(common_users.begin(),common_users.end(),gen); // shuffle
    common_users.erase(common_users.begin() + _number_of_users, common_users.end());// resize
    for(const auto &i:common_users){
        users.push_back(user(programs,i));
    }
}

void MainWindow::_generate_programs()
{
    vector<string>common_programs{"Google Chrome","Dropbox","Spotify","Paint","ShareX",
                                  "Iobit cleaner", "Anti-virus","Win RAR","Telegram",
                                  "Visual Studio", "Xcode","Cline","Source tree","Unity"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(common_programs.begin(),common_programs.end(),gen); // shuffle
    common_programs.erase(common_programs.begin() + _number_of_users, common_programs.end());// resize
    for(const auto &i:common_programs){
        programs.push_back(i);
    }
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<_number_of_users;
    qDebug()<<_number_of_programs;
    qDebug()<<_number_of_errors;
    qDebug()<<_hours_of_work;

    qDebug()<<"USERS";
    for(const auto &i:users){
        qDebug()<<QString::fromStdString(i.name());
    }
    qDebug()<<"";
    qDebug()<<"ERRORS";
    for(const auto &i:errors){
        qDebug()<<QString::fromStdString(i.error_name());
    }
    qDebug()<<"";
    qDebug()<<"Programs";
    for(const auto &i:programs){
        qDebug()<<QString::fromStdString(i);
    }
}
