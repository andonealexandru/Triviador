#include "Map.h"
#include <QPainter>
#include <QColor>
#include "Tile.h"
#include <stdio.h>
#include <QQueue>


Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Map::~Map()
{}

void Map::paintEvent(QPaintEvent* event)
{

	printf("Function called!\n");
	QPainter painter(this);
	painter.setPen(Qt::black);

	auto nLongitudinalSectors = 100;
	auto nTransveralSectors = 100;
	auto width = this->size().width();
	auto height = this->size().height();
	auto sectorWidth = width / nLongitudinalSectors;
	auto sectorHeight = height / nTransveralSectors;

	for (int i = 0; i < nTransveralSectors - 1; i++)
	{
		auto y = 0 + (i + 1) * sectorHeight;
		painter.drawLine(0, y, width, y);
	}

	for (int i = 0; i < nLongitudinalSectors - 1; i++)
	{
		auto x = 0 + (i + 1) * sectorWidth;
		painter.drawLine(x, 0, x, height);
	}

	QPixmap pixmap(sectorWidth, sectorHeight);
	pixmap.fill(Qt::yellow);
	painter.drawPixmap(0, 0, pixmap);

	int x = 37;
	int y = 37;

	//turn centru
	QColor gray(87, 96, 100), window(38, 175, 230), back(134, 132, 130);
	pixmap.fill(gray);
	for (int i = y - 3;i <= y + 3;i++)
		for (int j = x - 1;j <= x + 1;j++)
			painter.drawPixmap(j * sectorWidth, i * sectorHeight, pixmap);

	pixmap.fill(window);
	for (int i = -2;i < 2;i++)
		painter.drawPixmap(y * sectorWidth, (x + i) * sectorHeight, pixmap);

	pixmap.fill(gray);
	for (int i = 4;i <= 5;i++)
	{
		for (int j = x - 2;j <= x + 2;j++)
			painter.drawPixmap(j * sectorWidth, (y - i) * sectorHeight, pixmap);
	}

	for (int j = x - 1;j <= x + 1;j++)
		painter.drawPixmap(j * sectorWidth, (y - 6) * sectorHeight, pixmap);
}


