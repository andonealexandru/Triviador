#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QWidget>
#include <QLineEdit>
#include "SugestionAnswer.h"
#include "..\include\NumericQuestion.h"

NumericQuestion::NumericQuestion(int correctAnswer, std::string question, bool ho1, bool ho2, bool ho3, QWidget *parent)
	: m_correctAnswer(correctAnswer),
    m_question(question),
    m_ho1(ho1),
    m_ho2(ho2),
    m_ho3(ho3),
    QMainWindow(parent)
{
	ui.setupUi(this);
	ui.nqquestion->setText(QString::fromStdString(m_question));
    ui.nqanswer->setStyleSheet("background:#E1C16E;");
    timer();

    connect(ui.ho3, SIGNAL(clicked()), this, SLOT(ho3Clicked()));
    connect(ui.ho2, SIGNAL(clicked()), this, SLOT(ho2Clicked()));


    if (!ho1)ui.ho1->setVisible(false);
    if (!ho2)ui.ho2->setVisible(false);
    if (!ho3)ui.ho3->setVisible(false);
}

int NumericQuestion::timer()
{
    static int t = 30;
    if (t < 0)
        return t;
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

void NumericQuestion::ho3Clicked()
{
    int correctAnswer=5;
    QString text=QString::number(correctAnswer);
    ui.nqanswer->setText(text);
}

void NumericQuestion::ho2Clicked()
{
    SugestionAnswer *sa=new SugestionAnswer("intrebare", { "1","2","3","4"},"");
    sa->show();
}

NumericQuestion::~NumericQuestion()
{}
