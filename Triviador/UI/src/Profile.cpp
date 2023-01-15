#include "Profile.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

Profile::Profile(const std::pair<int, int>& statistics, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.GameCount->setText(("Game count: " + std::to_string(statistics.first)).data());
    ui.WonGames->setText(("Won games: " + std::to_string(statistics.second)).data());
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
    ui.GameCount->setStyleSheet("background:#E1C16E;");
    ui.WonGames->setStyleSheet("background:#E1C16E;");
}

void Profile::on_pushButtonExit_clicked()
{
	emit pushButtonExitPressed();
}

Profile::~Profile()
{}
