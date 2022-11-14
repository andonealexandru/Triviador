#include <User.h>

User::User(std::string name) : mName(std::move(name))
{}

User::User(uint8_t id, std::string name) : mId(id), mName(std::move(name))
{}

User::User(const User& other)
{
    mId = other.mId;
    mName = other.mName;
}

User& User::operator=(const User& other)
{
    if (this != &other)
    {
        mId = other.mId;
        mName = other.mName;
    }
    return *this;
}

uint8_t User::GetId()
{
    return mId;
}

std::string User::GetName()
{
    return mName;
}

void User::SetId(uint8_t id)
{
    mId = id;
}

void User::SetName(std::string name)
{
    mName = std::move(name);
}
