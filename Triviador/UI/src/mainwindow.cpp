#include "mainwindow.h"
#include "Login.h"
#include "Register.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui = new Ui::MainWindow();
    ui->setupUi(this);
    ui->startButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePageAfterLogin()
{
    ui->openButton->deleteLater();
    ui->openButton_2->deleteLater();
    ui->startButton->setVisible(true);
    delete registerWindow;
}

void MainWindow::changePageAfterRegister()
{
    ui->openButton->deleteLater();
    ui->openButton_2->deleteLater();
    ui->startButton->setVisible(true);
    delete loginWindow;
}

void MainWindow::on_openButton_clicked()
{
    loginWindow = new Login();
    QObject::connect(loginWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterRegister()));
    //functie care face legatura cu baza de date
    loginWindow->show();
}

void MainWindow::on_openButton_2_clicked()
{
    registerWindow = new Register();
    QObject::connect(registerWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterLogin()));
    //functie care face legatura cu baza de date

    registerWindow->show();
    
}


