#pragma once
#include <cstdint>

namespace DB
{
    class GameService
    {
    public:
        // constructors
        GameService() = default;
        GameService(uint8_t firstUserStatistics, uint8_t secondUserStatistics);
        GameService(uint8_t firstUserStatistics, uint8_t secondUserStatistics, uint8_t length);
        GameService(uint8_t id, uint8_t firstUserStatistics, uint8_t secondUserStatistics, uint8_t length);
        GameService(const GameService &other) = default;
        GameService &operator=(const GameService &other) = default;

        // getters
        uint8_t GetId() const;
        uint8_t GetFirstUserStatistics() const;
        uint8_t GetSecondUserStatistics() const;
        uint8_t GetLength() const;

        // setters
        void SetId(const uint8_t id);
        void SetFirstUserStatistics(const uint8_t userStatistics);
        void SetSecondUserStatistics(const uint8_t userStatistics);
        void SetLength(const uint8_t length);

    private:
        uint8_t m_id;
        uint8_t m_userStatistics1;
        uint8_t m_userStatistics2;
        uint8_t m_length;
    };
}
