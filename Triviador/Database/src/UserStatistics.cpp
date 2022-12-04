#include <UserStatistics.h>

namespace DB
{
    UserStatistics::UserStatistics(const uint32_t userId, const uint32_t gameCount, const uint32_t wonGames)
            : m_userId(userId), m_gameCount(gameCount), m_wonGames(wonGames)
    {
    }

    UserStatistics::UserStatistics(const uint32_t id, const uint32_t userId, const uint32_t gameCount, const uint32_t wonGames)
            : m_id(id), m_userId(userId), m_gameCount(gameCount), m_wonGames(wonGames)
    {
    }

    uint32_t UserStatistics::GetId() const{ return m_id; }
    uint32_t UserStatistics::GetUserId() const { return m_userId; }
    uint32_t UserStatistics::GetGameCount() const { return  m_gameCount; }
    uint32_t UserStatistics::GetWonGames() const { return m_wonGames; }

    void UserStatistics::SetId(const uint32_t id) { m_id = id; }
    void UserStatistics::SetUser(const uint32_t userId) { m_userId = userId; }
    void UserStatistics::SetGameCount(const uint32_t gameCount) { m_gameCount = gameCount; }
    void UserStatistics::SetWonGames(const uint32_t wonGames) { m_wonGames = wonGames; }

    void UserStatistics::AddGame() { ++m_gameCount; }
    void UserStatistics::AddWin()
    {
        ++m_gameCount;
        ++m_wonGames;
    }
}//namespace DB