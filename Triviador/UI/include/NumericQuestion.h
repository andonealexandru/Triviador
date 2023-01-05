#pragma once

#include <QMainWindow>
#include <QTimer>
#include "ui_NumericQuestion.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent* pe = nullptr) override;
	~NumericQuestion();
	void timer();

private:
	Ui::NumericQuestionClass ui;
};
