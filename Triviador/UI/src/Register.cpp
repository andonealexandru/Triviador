#include "Register.h"
#include <QPainter>
#include <QMessageBox>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Register::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    px.load(R"(C:\Users\mimu274175\Downloads\triviadorReg.jpg)");
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

Register::~Register()
{}

void Register::on_pushButtonExit_clicked()
{
    emit pushButtonExitPressed();
}

void Register::on_pushButton_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    json user =
    {
        {"name", username.toStdString()},
        {"password", password.toStdString()},
    };

    cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/users/register"},
                                    cpr::Body{to_string(user)});

    switch(response.status_code)
    {
        case 400:
            QMessageBox::warning(this, " ", "Eroare de server.");
            break;
        case 409:
            QMessageBox::warning(this, " ", "Utilizatorul exista deja.");
            break;
        case 201:
            QMessageBox::information(this, " ", "Utilizatorul a fost creat.");
            break;
        default:
            break;
    }

	emit pushButtonPressed();
}
