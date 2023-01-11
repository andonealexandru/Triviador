#include "Map.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include "Tile.h"
#include <QBrush>

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

	int nLongitudinalSectors = 300;
	int nTransveralSectors = 112;
	float width = 8*(this->size().width()/10);
	float height = this->size().height();
	float sectorWidth = width / nLongitudinalSectors;
	float sectorHeight = height / nTransveralSectors;

	QPixmap pixmap(sectorWidth+1, sectorHeight+1);
	pixmap.fill(Qt::black);

	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.IsBorder())
			{
				QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
				painter.drawPixmap(punct, pixmap);
			}

	pixmap.fill(Qt::blue);
	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.getParentRegion()->GetNumber()==1&&!tt.IsBorder())
				painter.drawPixmap(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight, pixmap);

	////paint score

	QPainter painter1(this);
	QFont font("Arial", 10, QFont::Bold);
	painter1.setFont(font);
	QPen pen(Qt::black,2);
	QBrush brush(Qt::blue);
	painter1.setPen(pen);
	painter1.setBrush(brush);
	
	float widthLabel = this->size().width()/25;
	float heightLabel = this->size().height()/25;

	std::vector<std::shared_ptr<Region>> map = g.getMap();
	for (auto i:map)
	{
		if (i->GetNumber())
		{
			std::pair<int,int>p=i->GetCenter();
			QRect rect(p.first*sectorWidth-widthLabel/2, p.second*sectorHeight-heightLabel/2, widthLabel, heightLabel);
			painter1.drawRect(rect);
			QString s = QString::number(300);
			painter1.drawText(rect, Qt::AlignCenter, s);
		}
	}

	//desenare playeri
	int nr_players = 2;
	for (int i = 0;i < nr_players;i++)
	{
		QPainter pt(this);
		QFont font("Arial", 12, QFont::Bold);
		pt.setFont(font);
		QPen pent(Qt::black, 3);
		QBrush brusht(Qt::yellow);
		pt.setPen(pent);
		pt.setBrush(brusht);


		QRect player(width, (height/nr_players)*i, 2 * (this->size().width() / 10)+5, this->size().height()/nr_players);
		pt.drawRect(player);
		pt.drawText(player, Qt::AlignCenter, "Monica:\n200");
	}
}


void Map::mouseReleaseEvent(QMouseEvent* ev)
{
	QPoint point = ev->pos();
	int x = point.x();
	int y = point.y();
	int ok = 0;
	int nLongitudinalSectors = 300;
	int nTransveralSectors = 112;
	float width = 8 * (this->size().width() / 10);
	float height = this->size().height();
	float sectorWidth = width / nLongitudinalSectors;
	float sectorHeight = height / nTransveralSectors;
	x = x/ sectorWidth;
	y = y/sectorHeight;
	for (std::vector<Tile> t : g.getTiles())
	{
		for (Tile tt : t)
			if (tt.GetCoordinate().second== x  && tt.GetCoordinate().first == y)
			{
				std::cout << "Ai dat click pe regiunea " << tt.getParentRegion()->GetNumber()<<std::endl;
				std::cout << x << " " << y <<std::endl;
				ok = 1;
				break;
			}
		if (ok == 1)
			break;
	}
}