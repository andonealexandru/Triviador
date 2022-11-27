#include <GameService.h>

namespace DB
{
    GameService::GameService(uint8_t firstUserStatistics, uint8_t secondUserStatistics):
        m_id(0)
        ,m_userStatistics1(firstUserStatistics)
        ,m_userStatistics2(secondUserStatistics)
        ,m_length(0)
    {
    }

    GameService::GameService(uint8_t firstUserStatistics, uint8_t secondUserStatistics, uint8_t lenght):
        m_id(0)
        ,m_userStatistics1(firstUserStatistics)
        ,m_userStatistics2(secondUserStatistics)
        ,m_length(lenght)
    {
    }

    GameService::GameService(uint8_t id, uint8_t firstUserStatistics, uint8_t secondUserStatistics, uint8_t lenght):
         m_id(id)
        ,m_userStatistics1(firstUserStatistics)
        ,m_userStatistics2(secondUserStatistics)
        ,m_length(lenght)
    {}

    uint8_t GameService::GetId() const { return m_id; }
    uint8_t GameService::GetFirstUserStatistics() const { return m_userStatistics1; }
    uint8_t GameService::GetSecondUserStatistics() const { return m_userStatistics2; }
    uint8_t GameService::GetLength() const { return m_length; }

    void GameService::SetId(const uint8_t id)  { m_id = id; }
    void GameService::SetFirstUserStatistics(const uint8_t userStatistics) { m_userStatistics1 = userStatistics; }
    void GameService::SetSecondUserStatistics(const uint8_t userStatistics) { m_userStatistics2 = userStatistics; }
    void GameService::SetLength(const uint8_t length) { m_length = length; }
}//namespace DB
