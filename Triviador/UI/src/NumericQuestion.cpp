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
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

NumericQuestion::NumericQuestion(const std::string& question,
                                 const int playerId,
                                 const std::string& playerName,
                                 const std::pair<bool, bool> powerups,
                                 QWidget *parent)
	: m_question{ question }
    , m_answer{ -1 }
    , m_t{ 30 }
    , m_powerupUsed{ false }
    , QMainWindow{ parent }
    , m_playerId{ playerId }
{
	ui.setupUi(this);
	ui.nqquestion->setText(QString::fromStdString(m_question));
    ui.player_name->setText(("Player: " + playerName).data());
    ui.nqanswer->setStyleSheet("background:#E1C16E;");
    timer();

    connect(ui.ho3, SIGNAL(clicked()), this, SLOT(ho3Clicked()));
    connect(ui.ho2, SIGNAL(clicked()), this, SLOT(ho2Clicked()));

    ui.sendButton->setVisible(true);
    ui.sendButton->setEnabled(true);
    ui.ho2->setVisible(true);
    ui.ho3->setVisible(true);
    ui.ho2->setEnabled(powerups.first);
    ui.ho3->setEnabled(powerups.second);
    ui.player_name->setStyleSheet("background:#E1C16E;");
}

NumericQuestion::~NumericQuestion()
{}


int NumericQuestion::timer()
{
    if (m_t < 0)
    {
        close();
        m_t = -1;
        m_answer = INT_MAX;
        emit sendButtonPressed();
        return m_t;
    }
    QTimer::singleShot(1 * 1000, this, &NumericQuestion::timer);
    QString str = QString::number(m_t);
    ui.nqclock->setText(str);
    ui.nqclock->setFont(QFont("Arial", 40));
    m_t--;
}

void NumericQuestion::setSugestionAnswer(const std::string& question, const std::vector<int>& answers)
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
    cpr::Response powerup = cpr::Get(cpr::Url{"localhost:18080/game/powerup/suggestAnswer"},
                                     cpr::Header{{ "ID", std::to_string(m_playerId) }});
    auto suggestedAnswer = json::parse(powerup.text)["answer"].get<int>();
    ui.nqanswer->setText(std::to_string(suggestedAnswer).data());
    m_powerupUsed = true;
}

void NumericQuestion::ho2Clicked()
{
    cpr::Response powerup = cpr::Get(cpr::Url{"localhost:18080/game/powerup/chooseAnswer"},
                                     cpr::Header{{ "ID", std::to_string(m_playerId) }});
    auto answers = json::parse(powerup.text).get<std::vector<int>>();
    setSugestionAnswer(m_question, answers);

    QObject::connect(m_sa, SIGNAL(a1Pressed()), this, SLOT(changePageAfterA1()));
    QObject::connect(m_sa, SIGNAL(a2Pressed()), this, SLOT(changePageAfterA2()));
    QObject::connect(m_sa, SIGNAL(a3Pressed()), this, SLOT(changePageAfterA3()));
    QObject::connect(m_sa, SIGNAL(a4Pressed()), this, SLOT(changePageAfterA4()));
    m_sa->show();

    m_powerupUsed = true;
}

void NumericQuestion::changePageAfterA1()
{
    ui.nqanswer->setText(std::to_string(m_sa->GetAnswers()[0]).data());
    delete m_sa;
}

void NumericQuestion::changePageAfterA2()
{
    ui.nqanswer->setText(std::to_string(m_sa->GetAnswers()[1]).data());
    delete m_sa;
}

void NumericQuestion::changePageAfterA3()
{
    ui.nqanswer->setText(std::to_string(m_sa->GetAnswers()[2]).data());
    delete m_sa;
}

void NumericQuestion::changePageAfterA4()
{
    ui.nqanswer->setText(std::to_string(m_sa->GetAnswers()[3]).data());
    delete m_sa;
}

void NumericQuestion::on_sendButton_clicked()
{
    Validator validator;
    QString answer = ui.nqanswer->text();
    std::cout << ui.nqanswer->text().toStdString() << "\n";
    if(validator.IsNumeric(answer.toStdString()))
    {
        std::cout << "validated!\n";
        m_answer = answer.toInt();
        emit sendButtonPressed();
    }
}

int NumericQuestion::GetAnswer() const { return m_answer; }
int NumericQuestion::GetRemainingTime() const { return m_t; }
bool NumericQuestion::PoweredUp() const { return m_powerupUsed; }



