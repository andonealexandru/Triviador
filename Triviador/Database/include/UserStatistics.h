#pragma once

#include <cstdint>
#include <memory>

namespace DB
{
    class UserStatistics
    {
    public:
        // constructors
        UserStatistics() = default;
        UserStatistics(uint32_t* userId, const uint32_t score, const uint32_t territoryCount);
        UserStatistics(const uint32_t id, uint32_t* userId, const uint32_t score, const uint32_t territoryCount);
        UserStatistics(const UserStatistics& other) = default;
        UserStatistics&operator=(const UserStatistics& other) = default;

        ~UserStatistics() = default;

        // getters
        uint32_t GetId() const;
        uint32_t* GetUserId() const;
        uint32_t GetGameCount() const;
        uint32_t GetWonGames() const;

        // setters
        void SetId(uint32_t id);
        void SetUser(uint32_t* user);
        void SetGameCount(const uint32_t gameCount);
        void SetWonGames(const uint32_t wonGames);

    private:
        uint32_t m_id;
        std::unique_ptr<uint32_t> m_userId;
        uint32_t m_gameCount;
        uint32_t m_wonGames;
    };
}//namespace DB
