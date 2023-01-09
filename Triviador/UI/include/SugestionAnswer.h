#pragma once
#include <QMainWindow>
#include "ui_SugestionAnswer.h"
#include <QPainter>
#include <QTimer>

class SugestionAnswer : public QMainWindow
{
	Q_OBJECT

public:
	SugestionAnswer(std::string question, std::vector<std::string>answers, int t, QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	void setQuestion();
	int timer();
	std::vector<std::string>GetAnswers();
	~SugestionAnswer();

signals:
	void a1Pressed();
	void a2Pressed();
	void a3Pressed();
	void a4Pressed();

private slots:
	void a1Clicked();
	void a2Clicked();
	void a3Clicked();
	void a4Clicked();

private:
	Ui::SugestionAnswerClass ui;
	std::string m_question;
	std::vector<std::string>m_answers;
	int m_t;
};
