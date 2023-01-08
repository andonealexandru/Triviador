#pragma once

#include <QMainWindow>
#include "ui_Profile.h"
#include<Qpainter>

class Profile : public QMainWindow
{
	Q_OBJECT

public:
	Profile(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~Profile();

signals:
	void pushButtonExitPressed();

private slots:
	void on_pushButtonExit_clicked();

private:
	Ui::ProfileClass ui;
};
