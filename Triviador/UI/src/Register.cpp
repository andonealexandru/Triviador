#include "Register.h"
#include "ui_Register.h"

Register::Register(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    emit pushButtonPressed();
}
