#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Game.h"
#include <QPainter>
#include <QMouseEvent>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget *parent = nullptr);
	~Map();
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* ev);
	Game g;

private:
	Ui::MapClass ui;
};

