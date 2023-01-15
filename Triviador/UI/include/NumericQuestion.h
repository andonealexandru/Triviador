#pragma once
#include <QMainWindow>
#include <QTimer>
#include "ui_NumericQuestion.h"
#include "SugestionAnswer.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(const std::string& question,
                    const int playerId,
                    const std::string& playerName,
                    const std::pair<bool, bool> powerups,
                    QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~NumericQuestion();

	int timer();

	void setSugestionAnswer(const std::string& question, const std::vector<int>& answers);
    int GetAnswer() const;
    int GetRemainingTime() const;
    bool PoweredUp() const;

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
    int m_playerId;
	std::string m_question;
    int m_answer;
    bool m_powerupUsed;
};
