#pragma once
#include <iostream>
#include <regex>

class __declspec(dllexport) Validator
{
public:
    explicit Validator();

    bool ValidatePassword(const std::string& password) const;
    bool ValidateUsername(const std::string& username) const;
    bool IsNumeric(const std::string& text) const;

private:
    std::regex m_passwordExpression;
    std::regex m_usernameExpression;
    std::regex m_numericExpression;
};

