#include <Question.h>

namespace DB
{
    Question::Question()
    {
    }

    Question::Question(std::string question, std::string category, Type type, std::optional<int32_t> answer) :
        m_question{ question }, m_category{ category }, m_type{ type }, m_answer{ answer }
    {
    }

    Question::Question(uint32_t id, std::string question, std::string category, Question::Type type,
        std::optional<int32_t> answer) :
        m_id{ id }, m_question{ question }, m_category{ category }, m_type{ type }, m_answer{ answer }
    {
    }

    Question::Question(const Question& other)
    {
        *this = other;
    }

    Question::Question(Question&& other)
    {
        *this = std::move(other);
    }

    Question& Question::operator=(const Question& other)
    {
        m_id = other.m_id;
        m_question = other.m_question;
        m_category = other.m_category;
        m_type = other.m_type;
        m_answer = other.m_answer;
        return *this;
    }

    Question& Question::operator=(Question&& other)
    {
        m_id = other.m_id;
        m_question = other.m_question;
        m_category = other.m_category;
        m_type = other.m_type;
        m_answer = other.m_answer;
        new (&other)Question;
        return *this;
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

    void Question::SetId(uint32_t id)
    {
        m_id = id;
    }

    void Question::SetQuestion(std::string question)
    {
        m_question = question;
    }

    void Question::SetCategory(std::string category)
    {
        m_category = category;
    }

    void Question::SetType(Type type)
    {
        m_type = type;
    }

    void Question::SetAnswer(std::optional<int32_t> answer)
    {
        m_answer = answer;
    }

}//namespace DB