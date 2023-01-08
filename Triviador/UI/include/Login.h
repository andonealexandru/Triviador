#pragma once

#include <QMainWindow>
#include "ui_Login.h"
#include <User.h>

class Login : public QMainWindow
{
	Q_OBJECT

public:
	Login(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~Login();

    DB::User GetUser() const;

signals:
	void pushButtonPressed();
	void pushButtonExitPressed();


private slots:
	void on_pushButton_clicked();
	void on_pushButtonExit_clicked();


private:
    DB::User* user;
	Ui::LoginClass ui;
};