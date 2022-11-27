#include "QuestionService.h"

namespace DB
{
    QuestionService::QuestionService(std::string question, std::string category, std::string type, int32_t answer)
            :
             m_question{ question }
            ,m_category{ category }
            ,m_type{ type }
            ,m_answer{ answer }
    {
    }

    QuestionService::QuestionService(uint32_t id, std::string question, std::string category, std::string type,
                                     int32_t answer)
                                     :
             m_id{ id }
            ,m_question{ question }
            ,m_category{ category }
            ,m_type{ type }
            ,m_answer{ answer }
    {
    }

    uint32_t QuestionService::GetId() const { return m_id; }
    std::string QuestionService::GetQuestion() const { return m_question; }
    std::string QuestionService::GetCategory() const { return m_category; }
    std::string QuestionService::GetType() const { return m_type; }
    int QuestionService::GetAnswer() const { return m_answer; }

    void QuestionService::SetId(const uint32_t id) { m_id = id; }
    void QuestionService::SetQuestion(const std::string& question) { m_question = question; }
    void QuestionService::SetCategory(const std::string& category) { m_category = category; }
    void QuestionService::SetType(const std::string& type) { m_type = type; }
    void QuestionService::SetAnswer(const int32_t answer) { m_answer = answer; }

}//namespace DB
