#ifndef TRIVIADOR_QUESTION_H
#define TRIVIADOR_QUESTION_H

#include "QuestionChoice.h"

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>

namespace Server {
    class Question {
    public:
        // constructors
        Question() = default;
        Question(const std::string& question, bool isMultipleChoice);
        Question(const std::string& question, bool isMultipleChoice,
                 const std::vector<Server::QuestionChoice<std::variant<int, std::string>>>& choices);

        ~Question() = default;
        // getters
        const std::string& GetQuestion() const;
        bool IsMultipleChoice() const;
        const std::vector<Server::QuestionChoice<std::variant<int, std::string>>>& GetChoices();

        // setters
        void SetQuestion(const std::string& question);
        void SetMultipleChoice(bool isMultipleChoice);

        void AddChoice(const Server::QuestionChoice<std::variant<int, std::string>>& questionChoice);
        void GetBestAnswers(std::vector<std::pair<int, int>> answers);

    private:
        std::string m_question;
        bool m_isMultipleChoice;
        std::vector<Server::QuestionChoice<std::variant<int, std::string>>> m_choices;
    };
}

#endif //TRIVIADOR_QUESTION_H
