#include "Login.h"
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Login::Login(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Login::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/triviador.jpg";
    px.load(imagePath.data());
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

    json user =
    {
        {"name", username.toStdString()},
        {"password", password.toStdString()},
    };

    cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/users/login"},
                                       cpr::Body{to_string(user)});

    switch(response.status_code)
    {
        case 400:
            QMessageBox::warning(this, " ", "Eroare de server.");
            break;
        case 409:
            QMessageBox::warning(this, " ", "Utilizatorul nu exista.");
            break;
        case 401:
            QMessageBox::warning(this, " ", "Parola incorecta.");
            break;
        case 200:
            QMessageBox::information(this, " ", "Conectare cu succes.");
            break;
        default:
            break;
    }

    emit pushButtonPressed();
}