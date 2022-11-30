#pragma once

#include <string>
#include <functional>
#include <optional>
namespace DB
{
    class Question
    {
    public:
        // constructors
        Question() = default;
        Question(const std::string& question, const std::string& category, const std::string& type, const int32_t answer);
        Question(const uint32_t id, const std::string& question, const std::string& category, const std::string& type, const int32_t answer);
        Question(const Question& other) = default;
        Question& operator=(const Question& other) = default;

        // getters
        uint32_t GetId() const;
        std::string GetQuestion() const;
        std::string GetCategory() const;
        std::string GetType() const;
        int32_t GetAnswer() const;

        //setters
        void SetId(const uint32_t id);
        void SetQuestion(const std::string& question);
        void SetCategory(const std::string& category);
        void SetType(const std::string& type);
        void SetAnswer(const int32_t answer);

    private:
        uint32_t m_id;
        std::string m_question;
        std::string m_category;
        std::string m_type;
        //std::optional<int32_t> m_answer;
        int32_t m_answer;
    };

}//namespace DB
