#pragma once

#include <QMainWindow>
#include "ui_Login.h"

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	~Login();

signals:
	void pushButtonPressed();

private slots:
	void on_pushButton_clicked();

private:
	Ui::LoginClass ui;
};
