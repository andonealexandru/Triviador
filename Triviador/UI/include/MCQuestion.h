#pragma once

#include <QMainWindow>
#include "ui_MCQuestion.h"

class MCQuestion : public QMainWindow
{
	Q_OBJECT

public:
	MCQuestion(QWidget *parent = nullptr);
	~MCQuestion();

private:
	Ui::MCQuestionClass ui;
};
