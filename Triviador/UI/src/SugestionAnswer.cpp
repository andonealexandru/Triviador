#include "SugestionAnswer.h"

SugestionAnswer::SugestionAnswer(std::string question, std::vector<std::string>answers,int t,QWidget *parent)
	: m_question(question),
	m_answers(answers),
	m_t(t),
	QMainWindow(parent)
{
	ui.setupUi(this);
	setQuestion();
	timer();
	connect(ui.a1, SIGNAL(clicked()), this, SLOT(a1Clicked()));
	connect(ui.a2, SIGNAL(clicked()), this, SLOT(a2Clicked()));
	connect(ui.a3, SIGNAL(clicked()), this, SLOT(a3Clicked()));
	connect(ui.a4, SIGNAL(clicked()), this, SLOT(a4Clicked()));
}

void SugestionAnswer::a1Clicked()
{
	emit a1Pressed();
}

void SugestionAnswer::a2Clicked()
{
	emit a2Pressed();
}

void SugestionAnswer::a3Clicked()
{
	emit a3Pressed();
}

void SugestionAnswer::a4Clicked()
{
	emit a4Pressed();
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
	ui.a1->setStyleSheet("background:#E1C16E;");
	ui.a2->setStyleSheet("background:#E1C16E;"); 
	ui.a3->setStyleSheet("background:#E1C16E;");
	ui.a4->setStyleSheet("background:#E1C16E;");
}

int SugestionAnswer::timer()
{
	if (m_t < 0)
	{
		close();
		return m_t;
	}
	QTimer::singleShot(1 * 1000, this, &SugestionAnswer::timer);
	QString str = QString::number(m_t);
	ui.timer->setText(str);
	ui.timer->setFont(QFont("Arial", 40));
	m_t--;
}

void SugestionAnswer::setQuestion()
{
	ui.question->setText(QString::fromStdString(m_question));
	ui.a1->setText(QString::fromStdString(m_answers[0]));
	ui.a2->setText(QString::fromStdString(m_answers[1]));
	ui.a3->setText(QString::fromStdString(m_answers[2]));
	ui.a4->setText(QString::fromStdString(m_answers[3]));
}

std::vector<std::string> SugestionAnswer::GetAnswers()
{
	return m_answers;
}

SugestionAnswer::~SugestionAnswer()
{}
