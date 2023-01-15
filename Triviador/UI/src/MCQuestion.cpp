#include "MCQuestion.h"
#include "QString"
#include "QGraphicsOpacityEffect"
#include <QPropertyAnimation>
#include <QTimer>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

MCQuestion::MCQuestion(const std::string& question, const int playerId,
                       const std::string& playerName,
                       const std::vector<std::pair<uint32_t, std::string>>& answers,
                       const bool powerupAvailable,
                       QWidget* parent)
	: m_question{ question }
    , m_t{ 30 }
    , m_selection{ -1 }
    , m_powerupUsed{ false }
    , m_playerId{ playerId }
    , QMainWindow{ parent }

{
	ui.setupUi(this);
    ui.ho1->setVisible(true);
    ui.ho1->setEnabled(powerupAvailable);
    ui.player_name->setText(("Player: " + playerName).data());
	timer();

    for(const auto& answer : answers)
    {
        auto&[id, choice] = answer;
        m_answers.emplace_back(DB::QuestionChoice{id, choice});
    }
    setQuestion();
}

void MCQuestion::setQuestion()
{
	ui.question->setText(m_question.data());
	ui.a1->setText(m_answers[0].GetChoice().data());
	ui.a2->setText(m_answers[1].GetChoice().data());
	ui.a3->setText(m_answers[2].GetChoice().data());
	ui.a4->setText(m_answers[3].GetChoice().data());
}

void MCQuestion::paintEvent(QPaintEvent* pe)
{
	QPixmap px;
	std::string imagePath = std::string(RESOURCE_DIR) + "/npQuestionpic.jpg";
	px.load(imagePath.data());
	QPainter paint(this);
	int widWidth = this->ui.centralWidget->width();
	int widHeight = this->ui.centralWidget->height();
	px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
	paint.drawPixmap(0, 0, px);
	ui.a1->setStyleSheet("background:#E1C16E;");
	ui.a2->setStyleSheet("background:#E1C16E;");
	ui.a3->setStyleSheet("background:#E1C16E;");
	ui.a4->setStyleSheet("background:#E1C16E;");
	ui.ho1->setStyleSheet("background:#E1C16E;");
	ui.ho2->setStyleSheet("background:#E1C16E;");
	ui.ho3->setStyleSheet("background:#E1C16E;");
    ui.player_name->setStyleSheet("background:#E1C16E;");

}

MCQuestion::~MCQuestion()
{}

int MCQuestion::timer()
{
    if (m_t < 0)
	{
		close();
        m_t = -1;
        m_selection = INT_MAX;
        emit clicked();
		return m_t;
	}
	QTimer::singleShot(1 * 1000, this, &MCQuestion::timer);
	QString str = QString::number(m_t);
	ui.mcquestion->setText(str);
	ui.mcquestion->setFont(QFont("Arial", 40));
	m_t--;
}

void MCQuestion::a1Clicked()
{
    m_selection = m_answers[0].GetId();
    emit clicked();
}

void MCQuestion::a2Clicked()
{
    m_selection = m_answers[1].GetId();
    emit clicked();
}

void MCQuestion::a3Clicked()
{
    m_selection = m_answers[2].GetId();
    emit clicked();
}

void MCQuestion::a4Clicked()
{
    m_selection = m_answers[3].GetId();
    emit clicked();
}

void MCQuestion::ho1Clicked()
{
    ui.a1->setVisible(false);
    ui.a4->setVisible(false);
    m_powerupUsed = true;
}

int MCQuestion::GetRemainingTime() const
{
    return m_t;
}

int MCQuestion::GetSelection() const
{
    return m_selection;
}

bool MCQuestion::PoweredUp() const
{
    return m_powerupUsed;
}

