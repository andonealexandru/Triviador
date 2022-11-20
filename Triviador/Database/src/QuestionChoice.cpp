#include <QuestionChoice.h>

namespace DB
{
	uint32_t QuestionChoice::getId() const
	{
		return m_id;
	}
	Question* QuestionChoice::getQuestion() const
	{
		return m_question;
	}
	std::string QuestionChoice::getChoice() const
	{
		return m_choice;
	}
	bool QuestionChoice::getIsCorect() const
	{
		return m_isCorect;
	}
}//namespace DB