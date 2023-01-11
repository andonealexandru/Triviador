#pragma once
#include <QMainWindow>
#include <QTimer>
#include "ui_NumericQuestion.h"
#include "SugestionAnswer.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(const std::string& question, QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~NumericQuestion();

	int timer();

	void setSugestionAnswer(const std::string& question, const std::vector<std::string>& answers);
    int GetAnswer() const;
    int GetRemainingTime() const;

public slots:
	void changePageAfterA1();
	void changePageAfterA2();
	void changePageAfterA3();
	void changePageAfterA4();


signals:
    void sendButtonPressed();


private slots:
	void ho3Clicked();
	void ho2Clicked();
    void on_sendButton_clicked();

private:
	Ui::NumericQuestionClass ui;
	SugestionAnswer* m_sa ;
	int m_t;
	std::string m_question;
    int m_answer;
};
