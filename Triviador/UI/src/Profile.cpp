#include "Profile.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

Profile::Profile(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
}

void Profile::paintEvent(QPaintEvent* pe)
{
	QPixmap px;
	std::string imagePath = std::string(RESOURCE_DIR) + "/triviador.jpg";
	px.load(imagePath.data());
	QPainter paint(this);
	int widWidth = this->ui.centralWidget->width();
	int widHeight = this->ui.centralWidget->height();
	px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
	paint.drawPixmap(0, 0, px);
	ui.pushButtonExit->setStyleSheet("background:#E1C16E;");

}

void Profile::on_pushButtonExit_clicked()
{
	emit pushButtonExitPressed();
}

Profile::~Profile()
{}
