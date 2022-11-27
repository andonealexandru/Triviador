#pragma once
#include <cstdint>
#include <memory>
namespace DB
{
    class UserStatisticsService
    {
    public:
        // constructors
        UserStatisticsService() = default;
        UserStatisticsService(const uint8_t userId, const uint8_t score, const uint8_t territoryCount);
        UserStatisticsService(uint8_t id, const uint8_t userId, uint8_t score, uint8_t territoryCount);
        UserStatisticsService(const UserStatisticsService &other) = default;
        UserStatisticsService &operator=(const UserStatisticsService &other) = default;

        ~UserStatisticsService() = default;

        // getters
        uint8_t GetId() const;
        uint8_t GetUserId() const;
        uint8_t GetScore() const;
        uint8_t GetTerritoryCount() const;

        // setters
        void SetId(uint8_t id);
        void SetUser(uint8_t* user);
        void SetScore(uint8_t score);
        void SetTerritoryCount(uint8_t territoryCount);

    public:
        uint8_t m_id;
        std::unique_ptr<uint8_t> m_userId;
        uint8_t m_score;
        uint8_t m_territoryCount;
    };
}//namespace DB
