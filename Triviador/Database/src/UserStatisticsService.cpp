#include <UserStatisticsService.h>
namespace DB
{
    UserStatisticsService::UserStatisticsService(uint8_t userId, uint8_t score, uint8_t territoryCount)
            : m_userId(&userId), m_score(score), m_territoryCount(territoryCount)
    {}

    UserStatisticsService::UserStatisticsService(uint8_t id, uint8_t userId, uint8_t score, uint8_t territoryCount)
            : m_id(id), m_userId(&userId), m_score(score), m_territoryCount(territoryCount)
    {}

    uint8_t UserStatisticsService::GetId() const{ return m_id; }
    uint8_t UserStatisticsService::GetUserId() const {return *m_userId;}
    uint8_t UserStatisticsService::GetScore() const { return m_score; }
    uint8_t UserStatisticsService::GetTerritoryCount() const {return m_territoryCount;}

    void UserStatisticsService::SetId(uint8_t id) { m_id = id; }
    void UserStatisticsService::SetUser(const uint8_t* userId) { m_userId.reset(const_cast<unsigned char *>(userId)); }
    void UserStatisticsService::SetScore(const uint8_t score) { m_score = score; }
    void UserStatisticsService::SetTerritoryCount(const uint8_t territoryCount) { m_territoryCount = territoryCount; }
}//namespace DB