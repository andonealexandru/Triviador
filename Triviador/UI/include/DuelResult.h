#pragma once

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "ui_DuelResult.h"

class DuelResult : public QMainWindow
{
	Q_OBJECT

public:
	DuelResult(const std::vector<std::tuple<int, std::string, int>>& players, QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~DuelResult();

private:
	Ui::DuelResultClass ui;
    std::vector<std::tuple<int, std::string, int>> m_players;
};
