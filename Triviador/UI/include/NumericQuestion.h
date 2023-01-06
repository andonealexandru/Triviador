#pragma once
#include <QMainWindow>
#include <QTimer>
#include "ui_NumericQuestion.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(int correctAnswer, std::string question, bool ho1, bool ho2, bool ho3, QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~NumericQuestion();
	int timer();

private slots:
	void ho3Clicked();
	void ho2Clicked();

private:
	Ui::NumericQuestionClass ui;
	int m_correctAnswer;
	std::string m_question;
	bool m_ho1, m_ho2, m_ho3; //variante ajutatoare
};
