#pragma once

#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "ui_DuelResult.h"

class DuelResult : public QMainWindow
{
	Q_OBJECT

public:
	DuelResult(std::vector<std::string> players, QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~DuelResult();

private:
	Ui::DuelResultClass ui;
	std::vector<std::string> m_players;
};
