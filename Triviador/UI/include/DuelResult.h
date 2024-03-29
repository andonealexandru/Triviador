#pragma once

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "ui_DuelResult.h"

class DuelResult : public QMainWindow
{
	Q_OBJECT

public:
	DuelResult(const std::vector<std::tuple<int, std::string, std::string>>& players,
               const std::string& correctAnswer, QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~DuelResult();

    void ShowEndGame(const std::vector<std::tuple<int, std::string, std::string>>& players);

private:
	Ui::DuelResultClass ui;
    std::vector<std::tuple<int, std::string, std::string>> m_players;
};
