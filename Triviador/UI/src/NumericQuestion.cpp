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
#include <Validator.h>

NumericQuestion::NumericQuestion(const std::string& question, QWidget *parent)
	: m_question(question)
    , m_answer(-1)
    , m_t(30)
    , QMainWindow(parent)
{
	ui.setupUi(this);
	ui.nqquestion->setText(QString::fromStdString(m_question));
    ui.nqanswer->setStyleSheet("background:#E1C16E;");
    timer();

    connect(ui.ho3, SIGNAL(clicked()), this, SLOT(ho3Clicked()));
    connect(ui.ho2, SIGNAL(clicked()), this, SLOT(ho2Clicked()));


    ui.sendButton->setVisible(true);
    ui.sendButton->setEnabled(true);
    ui.ho2->setVisible(true);
    ui.ho3->setVisible(true);
}

NumericQuestion::~NumericQuestion()
{}


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

void NumericQuestion::setSugestionAnswer(const std::string& question, const std::vector<std::string>& answers)
{
    m_sa = new SugestionAnswer(question, answers, m_t);
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
    ui.sendButton->setStyleSheet("background:#E1C16E;");
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
    setSugestionAnswer("intrebare", { "a","b","c","d" });

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

void NumericQuestion::on_sendButton_clicked()
{
    Validator validator;
    QString answer = ui.nqanswer->text();
    if(validator.IsNumeric(answer.toStdString()))
    {
        m_answer = answer.toInt();
        emit sendButtonPressed();
    }
}

int NumericQuestion::GetAnswer() const
{
    return m_answer;
}

int NumericQuestion::GetRemainingTime() const
{
    return m_t;
}



