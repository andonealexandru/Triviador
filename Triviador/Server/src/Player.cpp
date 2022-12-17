#include "Player.h"

Server::Player::Player(int id, const std::string& name)
    :
     m_id(id)
    ,m_name(name)
{}

int Server::Player::GetId() const {
    return m_id;
}

void Server::Player::SetId(int id) {
    m_id = id;
}

const std::string& Server::Player::GetName() const {
    return m_name;
}

void Server::Player::SetName(const std::string& name) {
    m_name = name;
}
