#pragma once
#include <string>
#include <functional>
#include <optional>

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
	Question(std::string question, std::string category, Type type, std::optional<int8_t> answer = std::none);
	Question(uint8_t id, std::string question, std::string category, Type type, std::optional<int8_t> answer = std::none);
	Question(const Question& other);
	Question& operator=(const Question& other);

	// getters
	uint8_t GetId();
	std::string GetQuestion();
	std::string GetCategory();
	Type GetType();
	std::optional<int8_t> GetAnswer();

	// setters


private:
	uint8_t mId;
	std::string mQuestion;
	std::string mCategory;
	Type mType;
	std::optional<int8_t> mAnswer;
};

