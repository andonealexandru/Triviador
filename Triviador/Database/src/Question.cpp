#include <Question.h>

namespace DB
{
    Question::Question(uint32_t id, std::string question, std::string category, int type,
                       std::optional<std::string> answer) :
            m_id{id}, m_question{question}, m_category{category}, m_type{type}, m_answer{answer}
{
}

}//namespace DB