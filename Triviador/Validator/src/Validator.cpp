#include "../include/Validator.h"

Validator::Validator()
        : m_passwordExpression{"\\w{5,}[0-9]+(\\w*)?"}
        , m_usernameExpression("[a-zA-Z]{3,}[0-9]*\\w*")
        , m_numericExpression("[0-9]+")
{
}

bool Validator::ValidatePassword(const std::string &password) const
{
    return std::regex_match(password, m_passwordExpression);
}

bool Validator::ValidateUsername(const std::string &username) const
{
    return std::regex_match(username, m_usernameExpression);
}

bool Validator::IsNumeric(const std::string &text) const
{
    return std::regex_match(text, m_numericExpression);
}
