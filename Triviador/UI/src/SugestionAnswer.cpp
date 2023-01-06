#include "SugestionAnswer.h"

SugestionAnswer::SugestionAnswer(std::string question, std::vector<std::string>answers, QString correctAnswer,QWidget *parent)
	: m_question(question),
	m_answers(answers),
	m_correctAnswer(correctAnswer),
	QMainWindow(parent)
{
	ui.setupUi(this);
	setQuestion();
	connect(ui.a1, SIGNAL(clicked()), this, SLOT(a1Clicked()));
	connect(ui.a2, SIGNAL(clicked()), this, SLOT(a2Clicked()));
	connect(ui.a3, SIGNAL(clicked()), this, SLOT(a3Clicked()));
	connect(ui.a4, SIGNAL(clicked()), this, SLOT(a4Clicked()));
}

void SugestionAnswer::a1Clicked()
{
}

void SugestionAnswer::a2Clicked()
{
}

void SugestionAnswer::a3Clicked()
{
}

void SugestionAnswer::a4Clicked()
{
}

void SugestionAnswer::paintEvent(QPaintEvent* pe)
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

void SugestionAnswer::setQuestion()
{
	ui.question->setText(QString::fromStdString(m_question));
	ui.a1->setText(QString::fromStdString(m_answers[0]));
	ui.a2->setText(QString::fromStdString(m_answers[1]));
	ui.a3->setText(QString::fromStdString(m_answers[2]));
	ui.a4->setText(QString::fromStdString(m_answers[3]));
}

SugestionAnswer::~SugestionAnswer()
{}
