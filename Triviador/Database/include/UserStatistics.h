#pragma once
#include <cstdint>
#include "User.h"

namespace DB
{
    class UserStatistics
    {
    public:
        // constructors
        UserStatistics(User *user, uint8_t score, uint8_t territoryCount);

        UserStatistics(uint8_t id, User *user, uint8_t score, uint8_t territoryCount);

        UserStatistics(const UserStatistics &other);

        UserStatistics &operator=(const UserStatistics &other);

        // getters
        uint8_t GetId();

        User *GetUser();

        uint8_t GetScore();

        uint8_t GetTerritoryCount();

        // setters
        void SetId(uint8_t id);

        void SetUser(User *user);

        void SetScore(uint8_t score);

        void SetTerritoryCount(uint8_t territoryCount);

    private:
        uint8_t m_id;
        User *m_user; // TODO: convert to smartpointer
        uint8_t m_score;
        uint8_t m_territoryCount;
    };
}//namespace DB