#pragma once
#include <string>
#include "Question.h"

namespace DB
{
    class QuestionChoice
    {
    public:
        //constructors
        QuestionChoice() = default;
        QuestionChoice(uint32_t id, Question* question, std::string choice, bool isCorect);
        QuestionChoice(const QuestionChoice& other) = default;
        QuestionChoice& operator=(const QuestionChoice& other);

        //getters
        uint32_t GetId() const;
        Question* GetQuestion() const;
        std::string GetChoice() const;
        bool GetIsCorect() const;

        //setters
        void SetId(const uint32_t id);
        void SetQuestion(Question* const question);
        void SetChoice(const std::string& choice);
        void SetIsCorect(const bool isCorect);

    protected:
        uint32_t m_id;
        Question *m_question;
        std::string m_choice;
        bool m_isCorect;

        friend class DBAccess;
    };


}//namespace DB
