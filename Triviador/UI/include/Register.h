#pragma once
#include <QMainWindow>
#include "ui_Register.h"
#include <User.h>

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~Register();

    DB::User GetUser() const;

signals:
	void pushButtonPressed();
	void pushButtonExitPressed();

private slots:
	void on_pushButton_clicked();
	void on_pushButtonExit_clicked();

private:
    DB::User* user;
	Ui::RegisterClass ui;
};
