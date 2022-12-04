#pragma once

#include <string>
#include <memory>

namespace DB
{
    class QuestionChoice
    {
    public:
        //constructors
        QuestionChoice() = default;
        QuestionChoice(const uint32_t id, const uint32_t questionId, const std::string& choice, const uint8_t isCorrect);
        QuestionChoice(const uint32_t questionId, const std::string& choice, const uint8_t isCorrect);
        QuestionChoice(const QuestionChoice& other);
        QuestionChoice& operator=(const QuestionChoice& other) = default;

        ~QuestionChoice() = default;

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

    private:
        uint32_t m_id;
        uint32_t m_questionId;
        std::string m_choice;
        uint8_t m_isCorrect;
    };

}//namespace DB
