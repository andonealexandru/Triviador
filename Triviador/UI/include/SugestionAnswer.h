#pragma once
#include <QMainWindow>
#include "ui_SugestionAnswer.h"
#include <QPainter>

class SugestionAnswer : public QMainWindow
{
	Q_OBJECT

public:
	SugestionAnswer(std::string question, std::vector<std::string>answers, QString correctAnswer,QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	QString answer();
	void setQuestion();
	~SugestionAnswer();

private slots:
	void a1Clicked();
	void a2Clicked();
	void a3Clicked();
	void a4Clicked();

private:
	Ui::SugestionAnswerClass ui;
	std::string m_question;
	std::vector<std::string>m_answers;

public:
	QString m_correctAnswer;
};
