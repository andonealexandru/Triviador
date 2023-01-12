#include "MCQuestion.h"
#include "QString"
#include "QGraphicsOpacityEffect"
#include <QPropertyAnimation>
#include <QTimer>
#include <iostream>

MCQuestion::MCQuestion(int correctAnswer,std::string question, std::vector<std::string>answers, bool ho1, bool ho2, bool ho3, QWidget* parent)
	: m_correctAnswer(correctAnswer),
	  m_question(question),
	  m_answers(answers),
	  m_ho1(ho1),
	  m_ho2(ho2),
	  m_ho3(ho3),
	  QMainWindow(parent)

{
	ui.setupUi(this);
	m_foundCorrectAnswer = false;

	connect(ui.a1, SIGNAL(clicked()), this, SLOT(a1Clicked()));
	connect(ui.a2, SIGNAL(clicked()), this, SLOT(a2Clicked()));
	connect(ui.a3, SIGNAL(clicked()), this, SLOT(a3Clicked()));
	connect(ui.a4, SIGNAL(clicked()), this, SLOT(a4Clicked()));

	connect(ui.ho1, SIGNAL(clicked()), this, SLOT(ho1Clicked()));

	if (!ho1)ui.ho1->setVisible(false);
	if (!ho2)ui.ho2->setVisible(false);
	if (!ho3)ui.ho3->setVisible(false);

	timer();
	setQuestion();
}

void MCQuestion::setQuestion()
{
	ui.question->setText(QString::fromStdString(m_question));
	ui.a1->setText(QString::fromStdString(m_answers[0]));
	ui.a2->setText(QString::fromStdString(m_answers[1]));
	ui.a3->setText(QString::fromStdString(m_answers[2]));
	ui.a4->setText(QString::fromStdString(m_answers[3]));
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

}

int MCQuestion::timer()
{
	static int t = 30;
	if (t < 0)
	{
		close();
		return t;
	}
	QTimer::singleShot(1 * 1000, this, &MCQuestion::timer);
	QString str = QString::number(t);
	ui.mcquestion->setText(str);
	ui.mcquestion->setFont(QFont("Arial", 40));
	t--;
}

void MCQuestion::a1Clicked()
{
	ui.a2->setDisabled(true);
	ui.a3->setDisabled(true);
	ui.a4->setDisabled(true);

	if (m_correctAnswer == 1)
		m_foundCorrectAnswer = true;
	std::cout << m_foundCorrectAnswer;
}

void MCQuestion::a2Clicked()
{
	ui.a1->setDisabled(true);
	ui.a3->setDisabled(true);
	ui.a4->setDisabled(true);

	if (m_correctAnswer == 2)
		m_foundCorrectAnswer = true;
	std::cout << m_foundCorrectAnswer;
}

void MCQuestion::a3Clicked()
{
	ui.a1->setDisabled(true);
	ui.a2->setDisabled(true);
	ui.a4->setDisabled(true);

	if (m_correctAnswer == 3)
		m_foundCorrectAnswer = true;
	std::cout << m_foundCorrectAnswer;
}

void MCQuestion::a4Clicked()
{
	ui.a1->setDisabled(true);
	ui.a2->setDisabled(true);
	ui.a3->setDisabled(true);
	ui.question->adjustSize();

	if (m_correctAnswer == 4)
		m_foundCorrectAnswer = true;
	std::cout << m_foundCorrectAnswer;
}

void MCQuestion::ho1Clicked()
{
	ui.a1->setVisible(false);
	ui.a4->setVisible(false);
}


MCQuestion::~MCQuestion()
{}