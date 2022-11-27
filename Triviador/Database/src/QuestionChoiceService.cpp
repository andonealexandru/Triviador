#include <QuestionChoiceService.h>

namespace DB
{

    QuestionChoiceService::QuestionChoiceService(uint32_t id, uint32_t questionId, std::string choice, uint8_t isCorrect):
            m_id{id}
            ,m_questionId{questionId}
            ,m_choice{choice}
            ,m_isCorrect{isCorrect}
    {
    }

    uint32_t QuestionChoiceService::GetId() const { return m_id; }
    uint32_t QuestionChoiceService::GetQuestionId() const { return m_questionId; }
    std::string QuestionChoiceService::GetChoice() const { return m_choice;}
    uint8_t QuestionChoiceService::GetIsCorrect() const { return m_isCorrect; }

    void QuestionChoiceService::SetId(const uint32_t id) { m_id = id; }
    void QuestionChoiceService::SetQuestionId(const uint32_t questionId) { m_questionId = questionId; }
    void QuestionChoiceService::SetChoice(const std::string& choice) { m_choice = choice; }
    void QuestionChoiceService::SetIsCorrect(const uint8_t isCorrect) { m_isCorrect = isCorrect; }

    QuestionChoice QuestionChoiceService::ToQuestionChoice(Question* question) const
    {
        return QuestionChoice(m_id, question, m_choice, static_cast<bool>(m_isCorrect));
    }
}//namespace DB