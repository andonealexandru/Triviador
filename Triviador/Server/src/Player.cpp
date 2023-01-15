#include "Player.h"

Server::Player::Player(int id, int userId, int score, Status status)
    :
     m_id(id)
    ,m_status(status)
    ,m_score(score)
    ,m_user(std::make_shared<DB::User>(DB::DBAccess::GetInstance()->Get<DB::User>(userId)))
    ,m_powerups(true, true, true)
{}

Server::Player::Player(const Server::Player &other)
    :
     m_id(other.m_id)
    ,m_status(other.m_status)
    ,m_score(other.m_score)
    ,m_user(std::make_shared<DB::User>(*other.GetUser()))
    ,m_powerups(other.m_powerups)
{}

Server::Player &Server::Player::operator=(const Server::Player &other) {
    m_id = other.m_id;
    m_status = other.m_status;
    m_score = other.m_score;
    m_user = std::make_shared<DB::User>(*other.GetUser());
    m_powerups = other.m_powerups;
    return *this;
}

int Server::Player::GetId() const {
    return m_id;
}

std::shared_ptr<DB::User> Server::Player::GetUser() const {
    return m_user;
}

void Server::Player::SetId(int id) {
    m_id = id;
}

void Server::Player::SetStatus(Status status) {
    m_status = status;
}

void Server::Player::SetUser(int userId) {
    //TODO
}

Server::Status Server::Player::GetStatus() const {
    return m_status;
}

int Server::Player::GetScore() const {
    return m_score;
}

void Server::Player::SetScore(int score) {
    m_score = score;
}

void Server::Player::IncrementScore() {
    m_score += 100;
}

void Server::Player::DecrementScore() {
    m_score -= 100;
}

void Server::Player::DisablePowerup(int index)
{
    switch(index)
    {
        case 0:
            std::get<0>(m_powerups) = false;
            break;
        case 1:
            std::get<1>(m_powerups) = false;
            break;
        case 2:
            std::get<2>(m_powerups) = false;
            break;
        default:
            break;
    }
}

bool Server::Player::GetPowerup(int index) const
{
    switch(index)
    {
        case 0:
            return std::get<0>(m_powerups);
        case 1:
            return std::get<1>(m_powerups);
        case 2:
            return std::get<2>(m_powerups);
        default:
            return false;
    }
}



