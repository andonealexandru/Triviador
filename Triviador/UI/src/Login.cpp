#include "Login.h"
#include <QPainter>
#include <QMessageBox>
#include <iostream>

Login::Login(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Login::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    px.load("F:/AN_2/loginpic.jpg");
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

Login::~Login()
{}

void Login::on_pushButtonExit_clicked()
{
    emit pushButtonExitPressed();
}


void Login::on_pushButton_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    int error = 400;

    if (error == 400)
        QMessageBox::warning(this, " ", "Eroare de server.");
    if (error == 409)
        QMessageBox::warning(this, " ", "Utilizatorul nu exista.");
    if (error == 401)
        QMessageBox::warning(this, " ", "Parola incorecta.");
    if (error == 200)
        QMessageBox::information(this, " ", "Conectare cu succes.");
    emit pushButtonPressed();
}