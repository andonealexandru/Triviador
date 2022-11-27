#pragma once

#include <string>
#include <functional>
#include <Question.h>
#include <optional>
namespace DB
{
    class QuestionService
    {
    public:
        // constructors
        QuestionService() = default;
        QuestionService(std::string question, std::string category, std::string type, int32_t answer);
        QuestionService(uint32_t id, std::string question, std::string category, std::string type, int32_t answer);
        QuestionService(const QuestionService& other) = default;
        QuestionService& operator=(const QuestionService& other) = default;

        // getters
        uint32_t GetId() const;
        std::string GetQuestion() const;
        std::string GetCategory() const;
        std::string GetType() const;
        int GetAnswer() const;

        //setters
        void SetId(const uint32_t id);
        void SetQuestion(const std::string& question);
        void SetCategory(const std::string& category);
        void SetType(const std::string& type);
        void SetAnswer(const int32_t answer);

        [[nodiscard]] Question ToQuestion() const;
    private:
        static Question::Type ConvertToType(const std::string& type) ;

        uint32_t m_id;
        std::string m_question;
        std::string m_category;
        std::string m_type;
        int32_t m_answer;

        friend class DBAccess;
    };

}//namespace DB
