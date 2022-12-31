#include "Map.h"
#include <QPainter>
#include <QColor>
#include "Tile.h"

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	g.ReadMap();
}

Map::~Map()
{}

void Map::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::black);

	int nLongitudinalSectors = 100;
	int nTransveralSectors = 100;
	float width = this->size().width();
	float height = this->size().height();
	float sectorWidth = width / nLongitudinalSectors;
	float sectorHeight = height / nTransveralSectors;

	QPixmap pixmap(sectorWidth+1, sectorHeight+1);
	pixmap.fill(Qt::black);

	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.IsBorder())
			{
				QPointF punct(tt.GetCoordinate().first * sectorWidth, tt.GetCoordinate().second * sectorHeight);
				painter.drawPixmap(punct, pixmap);
			}

	pixmap.fill(Qt::blue);
	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.getParentRegion()->GetNumber()==1&&!tt.IsBorder())
				painter.drawPixmap(tt.GetCoordinate().first * sectorWidth, tt.GetCoordinate().second * sectorHeight, pixmap);
}

void Map::mouseReleaseEvent(QMouseEvent* ev)
{
	QPoint point = ev->pos();
	int x = point.x();
	int y = point.y();
	int ok = 0;
	auto width = this->size().width();
	auto height = this->size().height();
	auto sectorWidth = width / 100;
	auto sectorHeight = height / 100;
	x = x/ sectorWidth;
	y = y/sectorHeight;
	for (std::vector<Tile> t : g.getTiles())
	{
		for (Tile tt : t)
			if (tt.GetCoordinate().first== x  && tt.GetCoordinate().second == y)
			{
				std::cout << "Ai dat click pe regiunea " << tt.getParentRegion()->GetNumber()<<std::endl;
				ok = 1;
				break;
			}
		if (ok == 1)
			break;
	}
}