#include "Login.h"

Login::Login(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Login::~Login()
{}

void Login::on_pushButton_clicked()
{
	emit pushButtonPressed();
}
