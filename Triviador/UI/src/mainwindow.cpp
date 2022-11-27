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


    px.load("F:/AN_2/Regions_pics/Atos_red.png");
    px = px.scaled(widWidth / 4.75, widHeight / 4.1, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 3.45, widHeight / 7.58, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 2.585, widHeight / 5.9, widWidth / 21, widHeight / 11.5);
    p.setBrush(red);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Bucovina_blue.png");
    px = px.scaled(widWidth / 5.8, widHeight / 4.6, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 2.03, widHeight / 9.3, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.83, widHeight / 5.81, widWidth / 21, widHeight / 11.5);
    p.setBrush(blue);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Cultura_green.png");
    px = px.scaled(widWidth / 5.8, widHeight / 5.8, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.85, widHeight / 4.3, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.7, widHeight / 3.44, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Cheile_Bicazului_green.png");
    px = px.scaled(widWidth / 5.45, widHeight / 3.35, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 2.38, widHeight / 3.3, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 2.08, widHeight / 2.632, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Trandafiri_red.png");
    px = px.scaled(widWidth / 6.4, widHeight / 5.7, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.761, widHeight / 2.9, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.615, widHeight / 2.52, widWidth / 21, widHeight / 11.5);
    p.setBrush(red);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);

    px.load("F:/AN_2/Regions_pics/Evreii_red.png");
    px = px.scaled(widWidth / 7.5, widHeight / 7, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.685, widHeight / 2.035, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.579, widHeight / 1.935, widWidth / 21, widHeight / 11.5);
    p.setBrush(red);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Teatru_green.png");
    px = px.scaled(widWidth / 5.4, widHeight / 2.43, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 6.98, widHeight / 2.556, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 4.29, widHeight / 1.9, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Corvin_green.png");
    px = px.scaled(widWidth / 3.7, widHeight / 4.2, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 3.26, widHeight / 2.38, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 2.57, widHeight / 1.99, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Petrol_green.png");
    px = px.scaled(widWidth / 4.5, widHeight / 4.4, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 2.565, widHeight / 1.68, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 2.07, widHeight / 1.5, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Raul_Olt_red.png");
    px = px.scaled(widWidth / 5.5, widHeight / 3.25, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 3.3, widHeight / 1.56, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 2.746, widHeight / 1.3, widWidth / 21, widHeight / 11.5);
    p.setBrush(red);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Lacu_Sarat_blue.png");
    px = px.scaled(widWidth / 6.4, widHeight / 5.3, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.744, widHeight / 1.772, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.579, widHeight / 1.572, widWidth / 21, widHeight / 11.5);
    p.setBrush(blue);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Burebista_green.png");
    px = px.scaled(widWidth / 7.57, widHeight / 5, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 2.143, widHeight / 1.323, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.97, widHeight / 1.23, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Sfintii_Voievozi_red.png");
    px = px.scaled(widWidth / 7, widHeight / 7.5, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.708, widHeight / 1.34, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.564, widHeight / 1.318, widWidth / 21, widHeight / 11.5);
    p.setBrush(red);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);


    px.load("F:/AN_2/Regions_pics/Atlantida_green.png");
    px = px.scaled(widWidth / 6, widHeight / 3.35, Qt::IgnoreAspectRatio);
    pt.drawPixmap(widWidth / 1.51, widHeight / 1.58, px);
    QWidget::paintEvent(pe);

    r.setRect(widWidth / 1.38, widHeight / 1.375, widWidth / 21, widHeight / 11.5);
    p.setBrush(green);
    p.drawEllipse(r);
    s = QString::number(100);
    p.setFont(QFont("Arial", widWidth * widHeight / 55666));
    p.drawText(r, Qt::AlignCenter, s);
}

MainWindow::~MainWindow()
{
    delete ui;
}
