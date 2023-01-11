#include "Region.h"

void Server::Region::AddAdjacentRegion(std::shared_ptr<Region> region) {
    m_AdjacentRegions.push_back(region);
}

Server::Region::Region(int id)
    :
     m_Id(id)
    ,m_UserId(-1)
    ,m_isBase(false)
{}

Server::Region::Region()
    :
     m_Id(-1)
    ,m_UserId(-1)
    ,m_isBase(false)
{}

void Server::Region::SetId(int id) {
    m_Id = id;
}

void Server::Region::SetUserId(int userId) {
    m_UserId = userId;
}

int Server::Region::GetId() {
    return m_Id;
}

int Server::Region::GetUserId() {
    return m_UserId;
}

void Server::Region::MakeBase() {
    m_isBase = true;
}

bool Server::Region::IsBase() {
    return m_isBase;
}
