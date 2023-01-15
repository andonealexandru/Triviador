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
#include <unordered_map>
#include <RequestHandler.h>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(DB::User* = nullptr, QWidget *parent = nullptr);
	~Map();
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* ev);

private slots:
    void NumericAnswerSent();
    void AnswerSent();

signals:
    void MousePressed();

private:
    enum class State : uint8_t
    {
        InGame,
        StartNewGame,
        FirstQuestion,
        BaseChoice,
        RegionQuestion,
        RegionChoice,
        WaitingForAnswers,
        MapChanged,
        Answer,
        AllPlayersAnswered,
        Duel,
        AttackQuestion,
        PowerupRegionChoice,
        Endgame,
    };
    State StringToState(const std::string& state);

    enum class QuestionType : uint8_t
    {
        MULTIPLE_CHOICE,
        NUMERIC,
    };
    QuestionType StringToQuestionType(const std::string& state);

    void OnGoing();
    void NextQuestion(const QuestionType type,
                      const std::string& question,
                      const std::array<std::pair<uint32_t, std::string>, 4>* answers = nullptr);
    void SendAnswer(const int answer, int remainingTime) const;
    void ShowResults(const std::vector<std::tuple<int, std::string, std::string>>& players, const std::string& correctAnswer);
    void InitStateHandler();
    void UpdateRegions();
    void UpdatePlayers();
    void PostChosenRegion(const std::string& endPoint, const std::string toPost);

private:
	Ui::MapClass ui;
    Game g;
    DB::User* m_user;
    std::vector<std::tuple<int, int, int, std::string>> m_players;
    QTimer* m_timer;
    MCQuestion* m_question;
    NumericQuestion* m_nQuestion;
    DuelResult* m_duelResult;
    int m_selectedRegion;
    RequestHandler m_requestHandler;
    std::unordered_map<State, std::function<void()>> m_stateHandler;

};
