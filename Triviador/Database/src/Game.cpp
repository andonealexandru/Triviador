#include <Game.h>

namespace DB
{
    Game::Game()
            : m_id(0), m_userStatistics(std::make_pair(nullptr, nullptr)), m_length(0)
    {}

    Game::Game(UserStatistics *firstUserStatistics, UserStatistics *secondUserStatistics)
            : m_id(0), m_userStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), m_length(0)
    {}

    Game::Game(UserStatistics *firstUserStatistics, UserStatistics *secondUserStatistics, uint8_t length)
            : m_id(0), m_userStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), m_length(length)
    {}

    Game::Game(uint8_t id, UserStatistics *firstUserStatistics, UserStatistics *secondUserStatistics, uint8_t length)
            : m_id(id), m_userStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), m_length(length)
    {}

    Game::Game(const Game &other)
            : m_id(other.m_id),
              m_userStatistics(std::make_pair(other.m_userStatistics.first, other.m_userStatistics.second)),
              m_length(other.m_length)
    {}

    Game &Game::operator=(const Game &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_userStatistics = std::make_pair(other.m_userStatistics.first, other.m_userStatistics.second);
            m_length = other.m_length;
        }
        return *this;
    }

    uint8_t Game::GetId()
    {
        return m_id;
    }

    UserStatistics *Game::GetFirstUserStatistics()
    {
        return m_userStatistics.first;
    }

    UserStatistics *Game::GetSecondUserStatistics()
    {
        return m_userStatistics.second;
    }

    uint8_t Game::GetLength()
    {
        return m_length;
    }

    void Game::SetId(uint8_t id)
    {
        m_id = id;
    }

    void Game::SetFirstUserStatistics(UserStatistics *userStatistics)
    {
        m_userStatistics.first = userStatistics;
    }

    void Game::SetSecondUserStatistics(UserStatistics *userStatistics)
    {
        m_userStatistics.second = userStatistics;
    }

    void Game::SetLength(uint8_t length)
    {
        m_length = length;
    }
}//namespace DB
