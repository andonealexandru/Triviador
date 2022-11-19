#include <Question.h>

namespace DB
{
    Question::Question(std::string question, std::string category, Type type, std::optional<int32_t> answer) :
        m_question{ question }, m_category{ category }, m_type{ type }, m_answer{ answer }
    {
    }

    Question::Question(uint32_t id, std::string question, std::string category, Question::Type type,
        std::optional<int32_t> answer) :
        m_id{ id }, m_question{ question }, m_category{ category }, m_type{ type }, m_answer{ answer }
    {
    }

    uint32_t Question::GetId() const
    {
        return m_id;
    }

    std::string Question::GetQuestion() const
    {
        return m_question;
    }

    std::string Question::GetCategory() const
    {
        return m_category;
    }

    Question::Type Question::GetType() const
    {
        return m_type;
    }

    std::optional<int32_t> Question::GetAnswer() const
    {
        return m_answer;
    }

}//namespace DB