#include <UserStatistics.h>
namespace DB
{
    UserStatistics::UserStatistics(User *user, uint8_t score, uint8_t territoryCount)
            : mUser(user), mScore(score), mTerritoryCount(territoryCount)
    {}

    UserStatistics::UserStatistics(uint8_t id, User *user, uint8_t score, uint8_t territoryCount)
            : mId(id), mUser(user), mScore(score), mTerritoryCount(territoryCount)
    {}

    UserStatistics::UserStatistics(const UserStatistics &other)
            : mId(other.mId), mUser(other.mUser), mScore(other.mScore), mTerritoryCount(other.mTerritoryCount)
    {}

    UserStatistics &UserStatistics::operator=(const UserStatistics &other)
    {
        if (this != &other)
        {
            mId = other.mId;
            mUser = other.mUser;
            mScore = other.mScore;
            mTerritoryCount = other.mTerritoryCount;
        }
        return *this;
    }

    uint8_t UserStatistics::GetId()
    {
        return mId;
    }

    User *UserStatistics::GetUser()
    {
        return mUser;
    }

    uint8_t UserStatistics::GetScore()
    {
        return mScore;
    }

    uint8_t UserStatistics::GetTerritoryCount()
    {
        return mTerritoryCount;
    }

    void UserStatistics::SetId(uint8_t id)
    {
        mId = id;
    }

    void UserStatistics::SetUser(User *user)
    {
        mUser = user;
    }

    void UserStatistics::SetScore(uint8_t score)
    {
        mScore = score;
    }

    void UserStatistics::SetTerritoryCount(uint8_t territoryCount)
    {
        mTerritoryCount = territoryCount;
    }
}//namespace DB