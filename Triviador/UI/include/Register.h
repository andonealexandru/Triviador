#pragma once
#include <QMainWindow>
#include "ui_Register.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~Register();

signals:
	void pushButtonPressed();
	void pushButtonExitPressed();

private slots:
	void on_pushButton_clicked();
	void on_pushButtonExit_clicked();

private:
	Ui::RegisterClass ui;
};
