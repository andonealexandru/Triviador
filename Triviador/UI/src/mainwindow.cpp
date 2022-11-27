#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->hide();
}

void MainWindow::paintEvent(QPaintEvent* pe)
{
    //  map
    QColor green(0, 99, 37), red(146, 43, 33), blue(40, 116, 166);

    QPixmap px;
    px.load("F:/AN_2/longmap.png");
    QPainter paint(this);
    int widWidth = this->ui->centralwidget->width();
    int widHeight = this->ui->centralwidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
    QWidget::paintEvent(pe);

    // regions and points

    px.load("F:/AN_2/Regions_pics/Transilvania_green.png");
    QPainter pt(this);
    px = px.scaled(widWidth / 4.8, widHeight / 4.3, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 4.3, widHeight / 4.65, px);
    QWidget::paintEvent(pe);

    QPainter p(this);
    QRect r(widWidth / 3.05, widHeight / 3.22, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    QString s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);

}

MainWindow::~MainWindow()
{
    delete ui;
}
