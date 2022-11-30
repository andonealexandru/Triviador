#include <QuestionChoice.h>

namespace DB
{

    QuestionChoice::QuestionChoice(const uint32_t id, uint32_t questionId, const std::string& choice, const uint8_t isCorrect) :
             m_id{id}
            ,m_choice{choice}
            ,m_isCorrect{isCorrect}
    {
        m_questionId.reset(&questionId);
    }

    uint32_t QuestionChoice::GetId() const { return m_id; }
    uint32_t QuestionChoice::GetQuestionId() const { return *m_questionId; }
    std::string QuestionChoice::GetChoice() const { return m_choice; }
    uint8_t QuestionChoice::GetIsCorrect() const { return m_isCorrect; }

    void QuestionChoice::SetId(const uint32_t id) { m_id = id; }
    void QuestionChoice::SetQuestionId(uint32_t questionId) { m_questionId.reset(&questionId); }
    void QuestionChoice::SetChoice(const std::string& choice) { m_choice = choice; }
    void QuestionChoice::SetIsCorrect(const uint8_t isCorrect) { m_isCorrect = isCorrect; }

    QuestionChoice::QuestionChoice(const QuestionChoice& other)
    {
        m_id = other.m_id;
        m_isCorrect = other.m_isCorrect;
        m_choice = other.m_choice;
        m_questionId.reset(std::make_unique<uint32_t>(*other.m_questionId).get());
    }

}//namespace DB