#pragma once

#include <QMainWindow>
#include "ui_MCQuestion.h"
#include "QPainter"
#include <QPushButton>
#include <vector>

class MCQuestion : public QMainWindow
{
	Q_OBJECT

public:
	MCQuestion(int correctAnswer,std::string question, std::vector<std::string>answers,bool ho1,bool ho2, bool ho3, QWidget* parent = nullptr);
	void setQuestion();
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~MCQuestion();

private slots:
	void a1Clicked();
	void a2Clicked();

private:
	Ui::MCQuestionClass ui;
	int m_correctAnswer;
	std::string m_question;
	std::vector<std::string>m_answers;
	bool m_foundCorrectAnswer,m_ho1, m_ho2,m_ho3; //variante ajutatoare
};
