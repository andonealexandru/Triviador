#include "Register.h"
#include <QPainter>
#include <QMessageBox>

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Register::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    px.load("F:/AN_2/loginpic.jpg");
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
    int error=201;
    if(error == 400)
        QMessageBox::warning(this, " ","Eroare de server.");    
    if(error == 409)
        QMessageBox::warning(this, " ","Utilizatorul exista deja.");    
    if(error == 201)
        QMessageBox::information(this, " ","Utilizatorul a fost creat.");
	emit pushButtonPressed();
}
