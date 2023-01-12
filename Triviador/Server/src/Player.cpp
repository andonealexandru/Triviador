#include "Player.h"

Server::Player::Player(int id, int userId, Status status)
    :
     m_id(id)
    ,m_status(status)
    ,m_user(std::make_shared<DB::User>(DB::DBAccess::GetInstance()->Get<DB::User>(userId)))
{}

Server::Player::Player(const Server::Player &other)
    :
     m_id(other.m_id)
    ,m_status(other.m_status)
    ,m_user(std::make_shared<DB::User>(*other.GetUser()))
{}

Server::Player &Server::Player::operator=(const Server::Player &other) {
    m_id = other.m_id;
    m_status = other.m_status;
    m_user = std::make_shared<DB::User>(*other.GetUser());
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

