#include "mainwindow.h"
#include "Login.h"
#include "Register.h"
#include "Profile.h"
#include <QPainter>
#include <QMessageBox>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginWindow(nullptr)
    , registerWindow(nullptr)
    , lobbyWindow(nullptr)
    , profileWindow(nullptr)
    , gameWindow(nullptr)
{
    ui->setupUi(this);
    ui->startButton->setVisible(false);
    ui->profileButton->setVisible(true);
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
    ui->startButton->setStyleSheet("background:#E1C16E;");
    ui->openButton->setStyleSheet("background:#E1C16E;");
    ui->openButton_2->setStyleSheet("background:#E1C16E;");
    ui->profileButton->setStyleSheet("background:#E1C16E;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePageAfterLogin()
{
    ui->openButton->hide();
    ui->openButton_2->hide();
    user = loginWindow->GetUser();
    ui->startButton->setVisible(true);
    delete loginWindow;
}

void MainWindow::changePageAfterRegister()
{
    ui->openButton->hide();
    ui->openButton_2->hide();
    user = registerWindow->GetUser();
    ui->startButton->setVisible(true);
    delete registerWindow;
}

void MainWindow::changePageAfterLobby()
{
    std::cout << "Game is starting\n";
    gameWindow = new Map(&this->user);
    gameWindow->show();
    delete lobbyWindow;
}


void MainWindow::changePageAfterExitRegister()
{
    delete registerWindow;
}

void MainWindow::changePageAfterExitLogin()
{
    delete loginWindow;
}

void MainWindow::changePageAfterExitLobby()
{
    delete lobbyWindow;
}

void MainWindow::changePageAfterExitProfile()
{
    delete profileWindow;
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

void MainWindow::on_profileButton_clicked()
{
    profileWindow = new Profile();
    QObject::connect(profileWindow, SIGNAL(pushButtonExitPressed()), this, SLOT(changePageAfterExitProfile()));
    profileWindow->show();
}

void MainWindow::on_startButton_clicked()
{
    cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/lobby/join"},
                                       cpr::Body(to_string(json())),
                                       cpr::Header{{"ID", std::to_string(user.GetId())}});

    lobbyWindow = new Lobby(user);
    QObject::connect(lobbyWindow, SIGNAL(startButtonPressed()), this, SLOT(changePageAfterLobby()));
    QObject::connect(lobbyWindow, SIGNAL(exitButtonPressed()), this, SLOT(changePageAfterExitLobby()));
    lobbyWindow->show();
    this->hide();
}






