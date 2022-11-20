#include <UserStatistics.h>
namespace DB
{
    UserStatistics::UserStatistics(User *user, uint8_t score, uint8_t territoryCount)
            : m_user(user), m_score(score), m_territoryCount(territoryCount)
    {}

    UserStatistics::UserStatistics(uint8_t id, User *user, uint8_t score, uint8_t territoryCount)
            : m_id(id), m_user(user), m_score(score), m_territoryCount(territoryCount)
    {}

    UserStatistics::UserStatistics(const UserStatistics &other)
            : m_id(other.m_id), m_user(other.m_user), m_score(other.m_score), m_territoryCount(other.m_territoryCount)
    {}

    UserStatistics &UserStatistics::operator=(const UserStatistics &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_user = other.m_user;
            m_score = other.m_score;
            m_territoryCount = other.m_territoryCount;
        }
        return *this;
    }

    uint8_t UserStatistics::GetId()
    {
        return m_id;
    }

    User *UserStatistics::GetUser()
    {
        return m_user;
    }

    uint8_t UserStatistics::GetScore()
    {
        return m_score;
    }

    uint8_t UserStatistics::GetTerritoryCount()
    {
        return m_territoryCount;
    }

    void UserStatistics::SetId(uint8_t id)
    {
        m_id = id;
    }

    void UserStatistics::SetUser(User *user)
    {
        m_user = user;
    }

    void UserStatistics::SetScore(uint8_t score)
    {
        m_score = score;
    }

    void UserStatistics::SetTerritoryCount(uint8_t territoryCount)
    {
        m_territoryCount = territoryCount;
    }
}//namespace DB