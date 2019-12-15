#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "user.h"
#include "error.h"

using std::vector;
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    vector <user> users;
    vector <error> errors;
    vector <string> programs;


    MainWindow(QWidget *parent = nullptr);

    void Set_number_of_users(int number);
    void Set_number_of_errors(int number);
    void Set_number_of_programs(int number);
    void Set_hours_of_work(int number);

    int hours_of_work();

    void generate_data();
    ~MainWindow();
signals:
    void data_arrived();

private slots:


    void on_setup_data_clicked();

    void on_Show_details_button_clicked();

    void on_start_demonstration_clicked();

private:
    user _search_user_by_name(string name);
    void problem_report();
    void _enter_amount_of_elements();
    /*
     * amount of elements in vector (from user's input)
     */
    int _number_of_users;
    int _number_of_errors;
    int _number_of_programs;
    int _hours_of_work;

    /*
     * generating names
     */
    void _generate_errors();
    void _generate_users();
    void _generate_programs();
    Ui::MainWindow *ui;


    vector<string> problems_appeared;
    int time_spend_on_fixing;
};
#endif // MAINWINDOW_H
