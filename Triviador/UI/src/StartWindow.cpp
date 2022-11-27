#include "StartWindow.h"
#include "ui_StartWindow.h"
#include "Login.h"
#include "ui_login.h"

StartWindow::StartWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    ui->startButton->setVisible(false);
    //this->centralWidget()->setStyleSheet("./background.jpg");
    //setLayout(Qt::Horizontal);
    //setStyleSheet("Qlabel{border-image:url (background.jpg);}");
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::changePageAfterLogin()
{
    ui->openButton->deleteLater();
    ui->openButton_2->deleteLater();
    ui->startButton->setVisible(true);
    delete webWindow;
}

void StartWindow::changePageAfterRegister()
{
    ui->openButton->deleteLater();
    ui->openButton_2->deleteLater();
    ui->startButton->setVisible(true);
    delete loginWindow;
}

void StartWindow::on_openButton_clicked()
{
    registerWindow = new Register();
    QObject::connect(registerWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterLogin()));
    //functie care face legatura cu baza de date

    registerWindow->show();
}

void StartWindow::on_openButton_2_clicked()
{
    StartWindow = new Login();
    QObject::connect(loginWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterRegister()));
    //functie care face legatura cu baza de date
    loginWindow->show();
}


