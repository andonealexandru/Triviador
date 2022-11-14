#include <Question.h>

Question::Question(std::string question, std::string category, Type type, std::optional<int8_t> answer)
	:
	mId{},
	mQuestion{question},
	mCategory{category},
	mType{type},
	mAnswer{answer}
{
}
