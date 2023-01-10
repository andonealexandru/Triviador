#include "Register.h"
#include <QPainter>
#include <QMessageBox>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <Validator.h>

using json = nlohmann::json;

Register::Register(QWidget *parent)
	: QMainWindow(parent)
    , user(nullptr)
{
	ui.setupUi(this);
}

void Register::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/triviador.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    ui.pushButton->setStyleSheet("background:#E1C16E;");
    ui.pushButtonExit->setStyleSheet("background:#E1C16E;");
    paint.drawPixmap(0, 0, px);
}

Register::~Register()
{
    delete user;
}

void Register::on_pushButtonExit_clicked()
{
    emit pushButtonExitPressed();
}

void Register::on_pushButton_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    Validator validator;
    if(!validator.ValidateUsername(username.toStdString()))
    {
        QMessageBox::warning(this, " ", "Numele de utilizator nu corespunde cerintelor.\nNumele trebuie sa inceapa cu cel putin 3 litere.");
        return;
    }
    if(!validator.ValidatePassword(password.toStdString()))
    {
        QMessageBox::warning(this, " ", "Parola nu corespunde cerintelor.\nParola trebuie sa aiba cel putin 6 caractere, dintre care un cel putin un numar");
        return;
    }


    json userJson =
    {
        {"name", username.toStdString()},
        {"password", password.toStdString()},
    };

    cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/users/register"},
                                    cpr::Body{to_string(userJson)});

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

    int id = json::parse(response.text)["ID"].get<int>();
    user = new DB::User(id, username.toStdString(), password.toStdString());

	emit pushButtonPressed();
}

DB::User Register::GetUser() const
{
    return *user;
}
