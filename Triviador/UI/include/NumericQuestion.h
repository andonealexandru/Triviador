#pragma once

#include <QMainWindow>
#include "ui_NumericQuestion.h"

class NumericQuestion : public QMainWindow
{
	Q_OBJECT

public:
	NumericQuestion(QWidget *parent = nullptr);
	~NumericQuestion();

private:
	Ui::NumericQuestionClass ui;
};
