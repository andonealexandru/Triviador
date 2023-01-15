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
	MCQuestion(const std::string& question, const int playerId,
               const std::string& playerName,
               const std::array<std::pair<uint32_t, std::string>, 4>& answers,
               const bool powerupAvailable,
               QWidget* parent = nullptr);
	void setQuestion();
	void paintEvent(QPaintEvent* pe = nullptr) override;
	int timer();

	~MCQuestion();

    int GetRemainingTime() const;
    int GetSelection() const;
    bool PoweredUp() const;

signals:
    void clicked();

private slots:
    void on_a1_clicked();
    void on_a2_clicked();
    void on_a3_clicked();
    void on_a4_clicked();
	void on_ho1_clicked();

private:
	Ui::MCQuestionClass ui;
	std::string m_question;
	std::array<DB::QuestionChoice, 4> m_answers;
    int m_t;
    int m_selection;
    int m_playerId;
    bool m_powerupUsed;
};
