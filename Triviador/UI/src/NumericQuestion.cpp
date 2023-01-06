#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QWidget>
#include "..\include\NumericQuestion.h"

NumericQuestion::NumericQuestion(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.nqquestion->setText("In ce an a avut loc batalia de la Posada?");
    ui.nqanswer->setStyleSheet("background:#E1C16E;");
    timer();
}

void NumericQuestion::timer()
{
    static int t = 30;
    if (t < 0)
        return;
    QTimer::singleShot(1 * 1000, this, &NumericQuestion::timer);
    QString str = QString::number(t);
    ui.nqclock->setText(str);
    ui.nqclock->setFont(QFont("Arial", 40));
    t--;
}

void NumericQuestion::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/npQuestionpic.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

NumericQuestion::~NumericQuestion()
{}
