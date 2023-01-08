#include "Profile.h"

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
}

void Profile::on_pushButtonExit_clicked()
{
	emit pushButtonExitPressed();
}

Profile::~Profile()
{}
