#pragma once

#include <QMainWindow>
#include "ui_Register.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

signals:
	void pushButtonPressed();

private slots:
	void on_pushButton_clicked();

private:
	Ui::RegisterClass ui;
};
