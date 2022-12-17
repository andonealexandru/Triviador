#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Game.h"
#include <QPainter>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget *parent = nullptr);
	~Map();
	virtual void paintEvent(QPaintEvent* event);
	void fill(const QPoint& point, QColor act, QPainter& painter);

private:
	Ui::MapClass ui;
};

