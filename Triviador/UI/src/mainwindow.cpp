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
    //this->centralWidget()->setStyleSheet("./background.jpg");
    //setLayout(Qt::Horizontal);
    setStyleSheet("Qlabel{border-image:url (background.jpg);}");
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
    registerWindow = new Register();
    QObject::connect(registerWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterLogin()));
    //functie care face legatura cu baza de date

    registerWindow->show();
}

void MainWindow::on_openButton_2_clicked()
{
    loginWindow = new Login();
    QObject::connect(loginWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterRegister()));
    //functie care face legatura cu baza de date
    loginWindow->show();
}


