#pragma once
#include <string>
#include "Question.h"

namespace DB
{
    class QuestionChoice
    {
    public:
        //getters
        uint32_t getId() const;
        Question* getQuestion() const;
        std::string getChoice() const;
        bool getIsCorect() const;

    protected:
        uint32_t m_id;
        Question *m_question;
        std::string m_choice;
        bool m_isCorect;

        friend class DBAccess;
    };


}//namespace DB
