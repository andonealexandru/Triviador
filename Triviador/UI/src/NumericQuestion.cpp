#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QWidget>
#include <QLineEdit>
#include <Qstring>
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
    if (m_t < 0)
    {
        close();
        return m_t;
    }
    QTimer::singleShot(1 * 1000, this, &NumericQuestion::timer);
    QString str = QString::number(m_t);
    ui.nqclock->setText(str);
    ui.nqclock->setFont(QFont("Arial", 40));
    m_t--;
}

void NumericQuestion::setSugestionAnswer(std::string question, std::vector<std::string> answers,int t)
{
    m_sa = new SugestionAnswer(question, answers,m_t);
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
    ui.ho1->setStyleSheet("background:#E1C16E;");
    ui.ho2->setStyleSheet("background:#E1C16E;"); 
    ui.ho3->setStyleSheet("background:#E1C16E;");
}

void NumericQuestion::ho3Clicked()
{
    int correctAnswer=5;
    QString text=QString::number(correctAnswer);
    ui.nqanswer->setText(text);
}

void NumericQuestion::ho2Clicked()
{
    setSugestionAnswer("intrebare", { "a","b","c","d" },m_t);

    QObject::connect(m_sa, SIGNAL(a1Pressed()), this, SLOT(changePageAfterA1()));
    QObject::connect(m_sa, SIGNAL(a2Pressed()), this, SLOT(changePageAfterA2()));
    QObject::connect(m_sa, SIGNAL(a3Pressed()), this, SLOT(changePageAfterA3()));
    QObject::connect(m_sa, SIGNAL(a4Pressed()), this, SLOT(changePageAfterA4()));

    m_sa->show();
}

void NumericQuestion::changePageAfterA1()
{
    
    ui.nqanswer->setText(QString::fromStdString(m_sa->GetAnswers()[0]));
    delete m_sa;
}

void NumericQuestion::changePageAfterA2()
{
    ui.nqanswer->setText(QString::fromStdString(m_sa->GetAnswers()[1]));
    delete m_sa;

}

void NumericQuestion::changePageAfterA3()
{
    ui.nqanswer->setText(QString::fromStdString(m_sa->GetAnswers()[2]));
    delete m_sa;

}

void NumericQuestion::changePageAfterA4()
{
    ui.nqanswer->setText(QString::fromStdString(m_sa->GetAnswers()[3]));
        delete m_sa;

}

NumericQuestion::~NumericQuestion()
{}
