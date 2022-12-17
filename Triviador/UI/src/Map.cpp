#include "Map.h"
#include <QPainter>
#include <QColor>
#include "Tile.h"
#include <stdio.h>
#include <QQueue>


Map::Map(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Map::~Map()
{}

void Map::fill(const QPoint& point, QColor act, QPainter &painter)
{
	//QPainter painter(&image);
	QPen myPen = QPen();
	myPen.setWidth(1);
	painter.setPen(myPen);

	QQueue<QPoint> pixels;
	pixels.enqueue(point);
	while (pixels.isEmpty() == 0)
	{
		QPoint newPoint = pixels.dequeue();
		QColor actual;
		actual.fromRgb(QColor::rgb(newPoint));
		if (actual == act)
		{
			painter.drawPoint(newPoint);
			update();

			QPoint left((newPoint.x() - 1), newPoint.y());
			if (left.x() > 0 && left.x() < image.width() && image.pixel(left) == act.rgb())
			{
				pixels.enqueue(left);
				painter.drawPoint(left);
				update();
			}

			QPoint right((newPoint.x() + 1), newPoint.y());
			if (right.x() > 0 && right.x() < image.width() && image.pixel(right) == act.rgb())
			{
				pixels.enqueue(right);
				painter.drawPoint(right);
				update();
			}

			QPoint up((newPoint.x()), (newPoint.y() - 1));
			if (up.y() > 0 && up.y() < image.height() && image.pixel(up) == act.rgb())
			{
				pixels.enqueue(up);
				painter.drawPoint(up);
				update();
			}

			QPoint down((newPoint.x()), (newPoint.y() + 1));
			if (down.y() > 0 && down.y() < image.height() && image.pixel(down) == act.rgb())
			{
				pixels.enqueue(down);
				painter.drawPoint(down);
				update();
			}
		}
	}
}



