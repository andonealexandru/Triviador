#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Game.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <User.h>
#include <MCQuestion.h>
#include <NumericQuestion.h>
#include <DuelResult.h>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(DB::User* = nullptr, QWidget *parent = nullptr);
	~Map();
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* ev);
	Game g;

public slots:
    void NumericAnswerSent();
    void AnswerSent();

signals:
    void MousePressed();

private:
    enum class QuestionType : uint8_t
    {
        MULTIPLE_CHOICE,
        NUMERIC,
    };

    void OnGoing();
    void NextQuestion(const QuestionType type, const std::string& question, const std::vector<std::pair<uint32_t, std::string>>* answers = nullptr);
    void SendAnswer(const std::variant<int, std::string>& answer, int remainingTime) const;
    void ShowResults(const std::vector<std::tuple<int, std::string, int>>& players);

	Ui::MapClass ui;
    DB::User* m_user;
    QTimer* m_timer;
    MCQuestion* m_question;
    NumericQuestion* m_nQuestion;
    DuelResult* m_duelResult;
    int m_selectedRegion;
};

