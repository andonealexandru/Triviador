#include "DuelResult.h"


DuelResult::DuelResult(std::vector<std::string> players,QWidget *parent)
	: m_players(players),
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lb1->setText(QString::fromStdString("1. "+players[0]));
    ui.lb2->setText(QString::fromStdString("2. "+players[1]));
    if(players.size()>2)
        ui.lb3->setText(QString::fromStdString("3. "+players[2]));
    if(players.size()==4)
        ui.lb4->setText(QString::fromStdString("4. "+players[3]));
}

void DuelResult::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/duel.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

DuelResult::~DuelResult()
{}
