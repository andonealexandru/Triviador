#pragma once
#include <QMainWindow>
#include "ui_MCQuestion.h"
#include "QPainter"
#include <QPushButton>
#include <vector>
#include <QuestionChoice.h>

class MCQuestion : public QMainWindow
{
	Q_OBJECT

public:
	MCQuestion(const std::string& question, const std::vector<std::pair<uint32_t, std::string>>& answers, QWidget* parent = nullptr);
	void setQuestion();
	void paintEvent(QPaintEvent* pe = nullptr) override;
	int timer();

	~MCQuestion();

    int GetRemainingTime() const;
    int GetSelection() const;

signals:
    void clicked();

private slots:
	void a1Clicked();
	void a2Clicked();
	void a3Clicked();
	void a4Clicked();
	void ho1Clicked();

private:
	Ui::MCQuestionClass ui;
	std::string m_question;
	std::vector<DB::QuestionChoice> m_answers;
    int m_t;
    uint32_t m_selection;
};
