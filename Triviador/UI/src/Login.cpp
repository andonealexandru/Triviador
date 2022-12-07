#include "login.h"
#include "ui_Login.h"

Login::Login(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    emit pushButtonPressed();
}
