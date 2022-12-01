#include "Question.h"

namespace DB
{
    Question::Question(const std::string& question, const std::string& category, const std::string& type,
                                     const int32_t answer)
        :
         m_question{ question }
        ,m_category{ category }
        ,m_type{ type }
        ,m_answer{ answer }
    {
    }

    Question::Question(const uint32_t id, const std::string& question, const std::string& category, const std::string& type,
                                     const int32_t answer)
        :
         m_id{ id }
        ,m_question{ question }
        ,m_category{ category }
        ,m_type{ type }
        ,m_answer{ answer }
    {
    }

    uint32_t Question::GetId() const { return m_id; }
    std::string Question::GetQuestion() const { return m_question; }
    std::string Question::GetCategory() const { return m_category; }
    std::string Question::GetType() const { return m_type; }
    int32_t Question::GetAnswer() const 
    { 
        if (HasAnswer())
        {
            return m_answer.value();
        }
    }

    void Question::SetId(const uint32_t id) { m_id = id; }
    void Question::SetQuestion(const std::string& question) { m_question = question; }
    void Question::SetCategory(const std::string& category) { m_category = category; }
    void Question::SetType(const std::string& type) { m_type = type; }
    void Question::SetAnswer(const int32_t answer) { m_answer = answer; }

    bool Question::HasAnswer() const
    {
        return m_answer.has_value();
    }

}//namespace DB
