#pragma once
#include <string>
#include <QuestionService.h>
#include <QuestionChoice.h>

namespace DB
{
    class QuestionChoiceService
    {
    public:
        //constructors
        QuestionChoiceService() = default;
        QuestionChoiceService(uint32_t id, uint32_t questionId, std::string choice, uint8_t isCorrect);
        QuestionChoiceService(const QuestionChoiceService& other) = default;
        QuestionChoiceService& operator=(const QuestionChoiceService& other) = default;

        //getters
        uint32_t GetId() const;
        uint32_t GetQuestionId() const;
        std::string GetChoice() const;
        uint8_t GetIsCorrect() const;

        //setters
        void SetId(const uint32_t id);
        void SetQuestionId(const uint32_t questionId);
        void SetChoice(const std::string& choice);
        void SetIsCorrect(const uint8_t isCorrect);

        QuestionChoice ToQuestionChoice(Question* question = nullptr) const;
    private:
        uint32_t m_id;
        uint32_t m_questionId;
        std::string m_choice;
        uint8_t m_isCorrect;
    };


}//namespace DB
