#pragma once
#include <QMainWindow>
#include <QTimer>
#include "ui_NumericQuestion.h"
#include "SugestionAnswer.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(int correctAnswer, std::string question, bool ho1, bool ho2, bool ho3, QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~NumericQuestion();
	int timer();
	void setSugestionAnswer(std::string question, std::vector<std::string>answers,int t);

public slots:
	void changePageAfterA1();
	void changePageAfterA2();
	void changePageAfterA3();
	void changePageAfterA4();


private slots:
	void ho3Clicked();
	void ho2Clicked();

private:
	Ui::NumericQuestionClass ui;
	SugestionAnswer* m_sa ;
	int m_correctAnswer,m_t=30;
	std::string m_question;
	bool m_ho1, m_ho2, m_ho3; //variante ajutatoare
};
