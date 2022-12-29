#pragma once

#include <QMainWindow>
#include "ui_Login.h"

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~Login();

signals:
	void pushButtonPressed();
	void pushButtonExitPressed();


private slots:
	void on_pushButton_clicked();
	void on_pushButtonExit_clicked();


private:
	Ui::LoginClass ui;
};