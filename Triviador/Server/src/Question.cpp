#include "Question.h"

Server::Question::Question(const std::string &question, bool isMultipleChoice)
    :
     m_question(question)
    ,m_isMultipleChoice(isMultipleChoice)
{}

Server::Question::Question(const std::string& question, bool isMultipleChoice,
                           const std::vector<Server::QuestionChoice<std::variant<int, std::string>>> &choices)
   :
    m_question(question)
   ,m_isMultipleChoice(isMultipleChoice)
{
    for (const auto& answer : choices)
        m_choices.push_back(answer);
}

const std::string &Server::Question::GetQuestion() const {
    return m_question;
}

bool Server::Question::IsMultipleChoice() const {
    return m_isMultipleChoice;
}

const std::vector<Server::QuestionChoice<std::variant<int, std::string>>> &Server::Question::GetChoices() {
    return m_choices;
}

void Server::Question::SetQuestion(const std::string &question) {
    m_question = question;
}

void Server::Question::SetMultipleChoice(bool isMultipleChoice) {
    m_isMultipleChoice = isMultipleChoice;
}

void Server::Question::AddChoice(const Server::QuestionChoice<std::variant<int, std::string>>& questionChoice) {
    m_choices.push_back(questionChoice);
}

void Server::Question::GetBestAnswers(std::vector<std::pair<int, int>> answers) {
    int correctAnswer = std::get<int>(m_choices[0].GetChoice());

    for (int i = 0; i < answers.size() - 1; ++i)
        for (int j = i + 1; j < answers.size(); ++j)
            if (abs(correctAnswer - answers[i].second) > abs(correctAnswer - answers[j].second))
                std::swap(answers[i], answers[j]);
}

