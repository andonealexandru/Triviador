#pragma once
#include <string>
#include "Question.h"

class QuestionChoice
{
public:
	uint8_t mId;
	Question* mQuestion;
	std::string mChoice;
};

