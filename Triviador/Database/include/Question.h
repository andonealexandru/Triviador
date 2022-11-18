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
        Question() = default;

        Question(std::string question, std::string category, int type, std::optional<std::string> answer);

        Question(uint32_t id, std::string question, std::string category, int type, std::optional<std::string> answer);

        Question(const Question &other) = default;

        Question &operator=(const Question &other) = default;

        Question(Question &&other) = default;

        Question &operator=(Question &&other) = default;

        // getters
        uint32_t GetId() const { return m_id; }

        std::string GetQuestion() const;

        std::string GetCategory() const;

        Type GetType() const;

        std::optional<int8_t> GetAnswer() const;

    protected:
        uint32_t m_id;
        std::string m_question;
        std::string m_category;
        int m_type;
        std::optional<std::string> m_answer;

       friend class DBAccess;
    };

}//namespace DB
