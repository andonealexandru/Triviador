#pragma once
#include <string>
#include "Question.h"

namespace DB
{
    class QuestionChoice
    {
    public:
        //constructors
        QuestionChoice();
        QuestionChoice(uint32_t id, Question* question, std::string choice, bool isCorect);
        QuestionChoice(const QuestionChoice& other);
        QuestionChoice(QuestionChoice&& other);

        QuestionChoice& operator=(const QuestionChoice& other);
        QuestionChoice& operator=(QuestionChoice&& other);

        //getters
        uint32_t GetId() const;
        Question* GetQuestion() const;
        std::string GetChoice() const;
        bool GetIsCorect() const;

        //setters
        void SetId(uint32_t id);
        void SetQuestion(Question* question);
        void SetChoice(std::string choice);
        void SetIsCorect(bool isCorect);

    protected:
        uint32_t m_id;
        Question *m_question;
        std::string m_choice;
        bool m_isCorect;

        friend class DBAccess;
    };


}//namespace DB
