#include "Player.h"

Server::Player::Player(int id, const std::string& name, crow::websocket::connection* connection)
    :
     m_id(id)
    ,m_name(name)
    ,m_connection(connection)
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

crow::websocket::connection* Server::Player::GetConnection() const {
    return m_connection;
}

void Server::Player::SetConnection(crow::websocket::connection* connection) {
    m_connection = connection;
}