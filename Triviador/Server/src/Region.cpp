#include "Region.h"

void Server::Region::AddAdjacentRegion(const std::weak_ptr<Region> &region) {
    m_AdjacentRegions.push_back(region);
}

Server::Region::Region(int id)
    :
     m_Id(id)
    ,m_UserId(-1)
    ,m_isBase(false)
    ,m_Score(0)
{}

Server::Region::Region()
    :
     m_Id(-1)
    ,m_UserId(-1)
    ,m_isBase(false)
    ,m_Score(0)
{}

void Server::Region::SetId(int id) {
    m_Id = id;
}

void Server::Region::SetUserId(int userId) {
    m_UserId = userId;
}

int Server::Region::GetId() const {
    return m_Id;
}

int Server::Region::GetUserId() const {
    return m_UserId;
}

void Server::Region::MakeBase() {
    m_isBase = true;
    m_Score = 300;
}

bool Server::Region::IsBase() const {
    return m_isBase;
}

int Server::Region::GetScore() const {
    return m_Score;
}

void Server::Region::IncrementScore() {
    m_Score += 100;
}

void Server::Region::DecrementScore() {
    m_Score -= 100;
}

std::vector<std::weak_ptr<Server::Region>> Server::Region::GetAdjacentRegions() const {
    return m_AdjacentRegions;
}
