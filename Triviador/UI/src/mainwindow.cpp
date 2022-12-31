#include "mainwindow.h"
#include "Login.h"
#include "Register.h"
#include <QPainter>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui = new Ui::MainWindow();
    ui->setupUi(this);
    ui->startButton->setVisible(false);
}

void MainWindow::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/triviador.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui->centralwidget->width();
    int widHeight = this->ui->centralwidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
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
    delete loginWindow;
}

void MainWindow::changePageAfterRegister()
{
    ui->openButton->deleteLater();
    ui->openButton_2->deleteLater();
    ui->startButton->setVisible(true);
    delete registerWindow;
}

void MainWindow::changePageAfterExitRegister()
{
    delete registerWindow;
}

void MainWindow::changePageAfterExitLogin()
{
    delete loginWindow;
}


void MainWindow::on_openButton_clicked()
{
    registerWindow = new Register();
    QObject::connect(registerWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterRegister()));
    QObject::connect(registerWindow, SIGNAL(pushButtonExitPressed()), this, SLOT(changePageAfterExitRegister()));
    registerWindow->show();
}

void MainWindow::on_openButton_2_clicked()
{
    loginWindow = new Login();
    QObject::connect(loginWindow, SIGNAL(pushButtonPressed()), this, SLOT(changePageAfterLogin()));
    QObject::connect(loginWindow, SIGNAL(pushButtonExitPressed()), this, SLOT(changePageAfterExitLogin()));
    loginWindow->show();
}

