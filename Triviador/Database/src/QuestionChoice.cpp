#include <QuestionChoice.h>

namespace DB
{

	QuestionChoice::QuestionChoice(uint32_t id, Question* question, std::string choice, bool isCorect):
		m_id{id}
        ,m_question{question}
        ,m_choice{choice}
        ,m_isCorect{isCorect}
	{
	}


	QuestionChoice& QuestionChoice::operator=(const QuestionChoice& other)
	{
		m_id = other.m_id;
		m_question = other.m_question;
		m_choice = other.m_choice;
		m_isCorect = other.m_isCorect;
		return *this;
	}

	uint32_t QuestionChoice::GetId() const
	{
		return m_id;
	}
	Question* QuestionChoice::GetQuestion() const
	{
		return m_question;
	}
	std::string QuestionChoice::GetChoice() const
	{
		return m_choice;
	}
	bool QuestionChoice::GetIsCorect() const
	{
		return m_isCorect;
	}
	void QuestionChoice::SetId(const uint32_t id)
	{
		m_id = id;
	}
	void QuestionChoice::SetQuestion(Question* const question)
	{
		m_question = question;
	}
	void QuestionChoice::SetChoice(const std::string& choice)
	{
		m_choice = choice;
	}
	void QuestionChoice::SetIsCorect(const bool isCorect)
	{
		m_isCorect = isCorect;
	}
}//namespace DB