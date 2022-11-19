#pragma once

#include <string>
#include <functional>
#include <optional>
namespace DB
{
    class Question
    {
    public:
        enum class Type : uint8_t
        {
            SingleChoice,
            MultipleChoice,
            None
        };

    public:
        // constructors
        Question() = default;
        Question(std::string question, std::string category, Type type, std::optional<int32_t> answer);
        Question(uint32_t id, std::string question, std::string category, Type type, std::optional<int32_t> answer);
        Question(const Question& other) = default;
        Question& operator=(const Question& other) = default;
        Question(Question&& other) = default;
        Question& operator=(Question&& other) = default;

        // getters
        uint32_t GetId() const;
        std::string GetQuestion() const;
        std::string GetCategory() const;
        Type GetType() const;
        std::optional<int32_t> GetAnswer() const;

    protected:
        uint32_t m_id;
        std::string m_question;
        std::string m_category;
        Type m_type;
        std::optional<int32_t> m_answer;

        friend class DBAccess;
    };

}//namespace DB
