#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <random>
#include <QDebug>
#include "input_data.h"
#include <QListWidget>
#include <QLabel>
#include <QLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setEnable all except fill data
    ui->group_list_widget->setEnabled(false);
    ui->start_demonstration->setEnabled(false);
    connect(this,&MainWindow::data_arrived,[=](){
        ui->group_list_widget->setEnabled(true);
        ui->start_demonstration->setEnabled(true);
        ui->setup_data->setEnabled(false);
    });
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

int MainWindow::hours_of_work()
{
    return _hours_of_work;
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

void MainWindow::problem_report()
{
    QFont newFont("Courier", 24, QFont::Bold, false);
    QDialog *window = new QDialog(this);
//    QListWidget *list = new QListWidget;
//    list->setFont(newFont);
    QPushButton *OkButton = new QPushButton;
    OkButton->setText("OK");
    OkButton->setFont(newFont);

    QLabel *title = new QLabel(this);
    title->setFrameStyle(QFrame::Panel);

    title->setText("During " +  QString::number(_hours_of_work) + " hours");
    title->setFont(newFont);
    title->setAlignment(Qt::AlignHCenter);

    QLabel *details_label = new QLabel(this);
    details_label->setText("Spotted " +  QString::number(problems_appeared.size()) + " problems");
    details_label->setFont(newFont);
    QPushButton *details_button = new QPushButton(this);
    details_button->setText("Details");
    details_button->setFont(newFont);

    QHBoxLayout *details_layout = new QHBoxLayout;
    details_layout->addWidget(details_label,0);
    details_layout->addWidget(details_button,1);

    QLabel *time_spent_label = new QLabel(this);
    time_spent_label->setText("Spent " +  QString::number(time_spend_on_fixing) + " hours on fixing");
    time_spent_label->setFont(newFont);
    time_spent_label->setAlignment(Qt::AlignHCenter);

    QGridLayout *layout= new QGridLayout;

    layout->addWidget(title,0,0);
    layout->addLayout(details_layout,1,0);
    layout->addWidget(time_spent_label,2,0);
    layout->addWidget(OkButton,3,0);

    connect(OkButton,&QPushButton::clicked,[=](){
        window->hide();
    });
    window->setLayout(layout);
    window->show();
//    for(unsigned long i = 0;i<time_element.size();i++ ){
//        if(time_element[i].group()==time_element[ui->listWidget->currentRow()].group()){
//            list->addItem((QTime(0,0,0).addMSecs(time_element[i].time_in_miliseconds()).toString(display_format)));
//        }
//    }

    connect(OkButton,&QPushButton::clicked,[=](){
        window->hide();
    });
    connect(details_button,&QPushButton::clicked,[=](){

        QDialog *details_window = new QDialog(window);
        QListWidget *list = new QListWidget;
        list->setFont(newFont);
        for(const auto &i:problems_appeared){
             list->addItem(QString::fromStdString(i));
        }

        QPushButton *OKButton2 = new QPushButton(window);
        OKButton2->setText("OK");
        OKButton2->setFont(newFont);

        QVBoxLayout *vlayout = new QVBoxLayout;
        vlayout->addWidget(list,0);
        vlayout->addWidget(OKButton2,0);
        details_window->setLayout(vlayout);

        connect(OKButton2,&QPushButton::clicked,[=](){
            details_window->hide();
        });
        details_window->show();

    });
    window->setLayout(layout);
    window->show();
}

void MainWindow::on_setup_data_clicked()
{
    _enter_amount_of_elements();
}

void MainWindow::on_Show_details_button_clicked()
{

    string current_user_name = ui->listWidget->currentItem()->text().toStdString(); // empty issue

    user current_user=_search_user_by_name(current_user_name);


    QFont newFont("Courier", 24, QFont::Bold, false);
    QDialog *details_option_window = new QDialog(this);

    QHBoxLayout *hlayout = new QHBoxLayout;

    QPushButton *programs_button = new QPushButton(this);
    programs_button->setText("Programs");
    programs_button->setFont(newFont);

    QPushButton *errors_button = new QPushButton(this);
    errors_button->setText("Errors");
    errors_button->setFont(newFont);

    hlayout->addWidget(programs_button,0);
    hlayout->addWidget(errors_button,1);

    //connect x2
    // outputting list of errors
    connect(errors_button,&QPushButton::clicked,[=](){

        QLabel *details_label = new QLabel(details_option_window);
        details_label->setText("Debug story");
        details_label->setFont(newFont);
        details_label->setFrameStyle(QFrame::Panel);
        details_label->setAlignment(Qt::AlignHCenter);


        QDialog *details_window = new QDialog(details_option_window);
        QListWidget *list = new QListWidget;
        list->setFont(newFont);

        // outputing story of error
        for(const auto &i:current_user.story){
            if (i._time_of_fix==0){
             list->addItem(QString::fromStdString(i._bug + " " + "Spotted: " + std::to_string(i._time_of_appearence)+"th hour of work"
                                                  + " Not fixed"));
            }
            else{
                list->addItem(QString::fromStdString(i._bug + " " + "Spotted: " + std::to_string(i._time_of_appearence)+"th hour of work"
                                                     + " " +"Fixed: " +std::to_string(i._time_of_fix)+ "th hour of work"));

            }
        }

        QPushButton *OKButton2 = new QPushButton(details_option_window);
        OKButton2->setText("OK");
        OKButton2->setFont(newFont);

        QVBoxLayout *vlayout = new QVBoxLayout;

        vlayout->addWidget(details_label,0);
        vlayout->addWidget(list,1);
        vlayout->addWidget(OKButton2,2);
        details_window->setLayout(vlayout);

        connect(OKButton2,&QPushButton::clicked,[=](){
            details_window->hide();
        });
        details_window->setLayout(vlayout);
        details_window->show();

    });
    // outputing list of programs that used this worker
    connect(programs_button,&QPushButton::clicked,[=](){
        QLabel *details_program_label = new QLabel(details_option_window);
        details_program_label->setText("Program used");
        details_program_label->setFont(newFont);
        details_program_label->setFrameStyle(QFrame::Panel);
        details_program_label->setAlignment(Qt::AlignHCenter);


        QDialog *details_window = new QDialog(details_option_window);
        QListWidget *list = new QListWidget;
        list->setFont(newFont);

        // outputing programs that used this worker
        for(const auto &i:current_user.program_and_average_time){
             list->addItem(QString::fromStdString(i.first));
        }
        QPushButton *OKButton = new QPushButton(details_option_window);
        OKButton->setText("OK");
        OKButton->setFont(newFont);
        QVBoxLayout *vlayout = new QVBoxLayout;

        vlayout->addWidget(details_program_label,0);
        vlayout->addWidget(list,1);
        vlayout->addWidget(OKButton,2);
        details_window->setLayout(vlayout);

        connect(OKButton,&QPushButton::clicked,[=](){
            details_window->hide();
        });
        details_window->setLayout(vlayout);
        details_window->show();
    });

    details_option_window->setLayout(hlayout);
    details_option_window->show();
}

user MainWindow::_search_user_by_name(std::string name)
{
    user current_user;
    for(const auto &i:users){
        if(i.name()==name){
            current_user = i;
        }
    }
        return current_user;
}
/*
 * каждый работник должен выбрать програму (если он не занят)
 *
 */
void MainWindow::on_start_demonstration_clicked()
{
    int time_counter=0;
    while(time_counter<_hours_of_work){
        //each worker
        for(auto &i:users){
            // if he is not occupied
            if(!i.occupied()){
                // pick program
                  i.Set_occupied(true); // set occupied
                  i.pick_up_random_program(); // random program
                  i.create_time_of_usage();//generate time of usage
                  i.working_on_program(errors,time_counter); //start working with program
            }
            else { // if occupied check if he need to fix a bug
                if(i.bug_spotted){
                    i.current_bug_working_time_left--;
                    if(i.current_bug_working_time_left==0){ // if end up with a bug complete story about it
                        i.Set_time_of_fix(time_counter);
                        i.Set_occupied(false);
                    }
                    else{
                        i.Set_necessary_work_time(i.necessary_work_time()-1);
                        i.working_on_program(errors,time_counter); //start working with program
                    }
                }
            }
        }
        time_counter++;
    }
    for(const auto&i:users){
        time_spend_on_fixing=0;
        ui->listWidget->addItem(QString::fromStdString(i.name()));
        for(const auto &j:i.story){
            problems_appeared.push_back(j._bug);
            if(j._time_of_fix!=0){
                time_spend_on_fixing+=(j._time_of_fix-j._time_of_appearence);
            }
        }
    }
    problem_report();
}
