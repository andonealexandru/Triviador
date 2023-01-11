#include "Map.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include "Tile.h"
#include <QBrush>
#include<string>

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}


Map::~Map()
{}

void Map::paintEvent(QPaintEvent* event)
{
	if (g.GetNrPlayers())
	{
		std::vector<std::pair<QColor, QColor>> colors(5);
		colors[0].first = Qt::white;
		colors[0].second = QColor(205, 200, 200);
		colors[1].first = Qt::red;
		colors[1].second = QColor(223, 127, 127);
		colors[2].first = Qt::blue;
		colors[2].second = QColor(104, 104, 229);
		colors[3].first = Qt::green;
		colors[3].second = QColor(157, 232, 157);
		colors[4].first = Qt::yellow;
		colors[4].second = QColor(232, 232, 156);


		QPainter painter(this);
		painter.setPen(Qt::black);

		int nLongitudinalSectors = 300;
		int nTransveralSectors = 112;
		float width = 8 * (this->size().width() / 10);
		float height = this->size().height();
		float sectorWidth = width / nLongitudinalSectors;
		float sectorHeight = height / nTransveralSectors;

		QPixmap pixmap(sectorWidth + 1, sectorHeight + 1);
		pixmap.fill(Qt::black);

		//border
		for (std::vector<Tile> t : g.getTiles())
			for (Tile tt : t)
				if (tt.IsBorder())
				{
					QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
					painter.drawPixmap(punct, pixmap);
				}

		//fill

		std::vector<std::pair<QPixmap, QPixmap>> colorPixmaps;
		for (const auto& color : colors) 
		{
			QPixmap pixmap1(sectorWidth + 1, sectorHeight + 1);
			pixmap1.fill(color.first);
			QPixmap pixmap2(sectorWidth + 1, sectorHeight + 1);
			pixmap2.fill(color.second);
			colorPixmaps.emplace_back(pixmap1, pixmap2);
		}

		std::vector<std::vector<Tile>> aux = g.getTiles();
		for (std::vector<Tile> t : aux)
			for (Tile tt : t)
				if (!tt.IsBorder())
					if (!tt.getParentRegion()->GetHighlight())
					{
						QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
						painter.drawPixmap(punct, colorPixmaps[tt.getParentRegion()->GetUserId()].first);
					}
					else
					{
						QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
						painter.drawPixmap(punct, colorPixmaps[tt.getParentRegion()->GetUserId()].second);
					}

		////paint score

		float widthLabel = this->size().width() / 25;
		float heightLabel = this->size().height() / 25;

		std::vector<std::shared_ptr<Region>> map = g.getMap();
		for (auto i : map)
		{
			if (i->GetNumber())
			{
				QPainter painter1(this);
				QFont font("Arial", 10);
				painter1.setFont(font);
				QPen pen(Qt::black, 2);
				QBrush brush(Qt::white);
				painter1.setPen(pen);
				painter1.setBrush(brush);

				std::pair<int, int>p = i->GetCenter();
				
				if (i->IsBase())
				{
					QRect rect(p.first * sectorWidth - widthLabel / 2, p.second * sectorHeight - heightLabel / 2, widthLabel, heightLabel);
					painter1.drawEllipse(rect);
					QString s = QString::number(i->GetValue());
					painter1.drawText(rect, Qt::AlignCenter, s);
				}
				else
				{
					QRect rect(p.first * sectorWidth - widthLabel / 2, p.second * sectorHeight - heightLabel / 2, widthLabel, heightLabel / 1.2);
					painter1.drawRect(rect);
					QString s = QString::number(i->GetValue());
					painter1.drawText(rect, Qt::AlignCenter, s);
				}
			}
		}

		//desenare playeri
		for (int i = 0;i < g.GetNrPlayers();i++)
		{
			QPainter pt(this);
			QFont font("Arial", 12, QFont::Bold);
			pt.setFont(font);
			QPen pent(Qt::black, 3);
			QBrush brusht(QColor(185, 91, 36));
			pt.setPen(pent);
			pt.setBrush(brusht);

			QRect player(width, (height / g.GetNrPlayers()) * i, 2 * (this->size().width() / 10) + 5, this->size().height() / g.GetNrPlayers());
			pt.drawRect(player);
			pt.drawText(player, Qt::AlignCenter, "Monica:\n200");
		}
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