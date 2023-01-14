#include "Map.h"

#include <vector>

int Server::Map::GetId() const {
    return m_Id;
}

std::vector<int> Server::Map::GetValidBaseChoices() const {
    std::vector<int> validBases;

    /* all regions that:
     * are not base
     * don't have base neighbour
     */

    for (const auto& region : m_Regions) {
        if (region->IsBase())
            continue;

        bool hasBaseNeighbour = false;
        for (const auto& neighbour : region->GetAdjacentRegions()) {
            auto neighbourObj = neighbour.lock();
            if (neighbourObj->IsBase()) {
                hasBaseNeighbour = true;
                continue;
            }
        }

        if (!hasBaseNeighbour)
            validBases.push_back(region->GetId());
    }

    return validBases;
}

std::vector<int> Server::Map::GetValidRegionChoices(int userId) const {
    std::vector<int> validRegions;

    /* all regions that:
     * are not occupied
     * have neighbour owned by userId
     */

    for (const auto& region : m_Regions) {
        if (region->GetUserId() != -1)
            continue;

        bool hasUserNeighbour = false;
        for (const auto& neighbour : region->GetAdjacentRegions()) {
            auto neighbourObj = neighbour.lock();
            if (neighbourObj->GetUserId() == userId) {
                hasUserNeighbour = true;
                continue;
            }
        }

        if (hasUserNeighbour)
            validRegions.push_back(region->GetId());
    }

    return validRegions;
}

bool Server::Map::AllRegionsOccupied() const {
    for (const auto& region : m_Regions) {
        if (region->GetUserId() == -1)
            return false;
    }
    return true;
}

void Server::Map::GenerateTwoPlayerMap() {
    m_Id = 1;

    for (int i = 0; i < 9; i++) {
        m_Regions.push_back(std::make_shared<Region>(Region(i+1)));
    }

    // 1st region
    m_Regions[0]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[2]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[3]);

    // 2nd region
    m_Regions[1]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[1]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[1]->AddAdjacentRegion(m_Regions[4]);

    // 3rd region
    m_Regions[2]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[2]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[2]->AddAdjacentRegion(m_Regions[5]);

    // 4th region
    m_Regions[3]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[5]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[2]);

    // 5th region
    m_Regions[4]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[8]);

    // 6th region
    m_Regions[5]->AddAdjacentRegion(m_Regions[2]);
    m_Regions[5]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[5]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[5]->AddAdjacentRegion(m_Regions[7]);

    // 7th region
    m_Regions[6]->AddAdjacentRegion(m_Regions[5]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[8]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[7]);

    // 8th region
    m_Regions[7]->AddAdjacentRegion(m_Regions[5]);
    m_Regions[7]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[7]->AddAdjacentRegion(m_Regions[8]);

    // 9th region
    m_Regions[8]->AddAdjacentRegion(m_Regions[7]);
    m_Regions[8]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[8]->AddAdjacentRegion(m_Regions[4]);
}

void Server::Map::GenerateThreePlayerMap() {
    m_Id = 2;
    // m_Regions.resize(15);

    for (int i = 0; i < 15; i++) {
        m_Regions.push_back(std::make_shared<Region>(Region(i+1)));
        //m_Regions[i]->SetId(i + 1);
    }

    // 1st region
    m_Regions[0]->AddAdjacentRegion(m_Regions[8]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[12]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[14]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[0]->AddAdjacentRegion(m_Regions[4]);

    // 2nd region
    m_Regions[1]->AddAdjacentRegion(m_Regions[2]);
    m_Regions[1]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[1]->AddAdjacentRegion(m_Regions[3]);

    // 3rd region
    m_Regions[2]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[2]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[2]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[2]->AddAdjacentRegion(m_Regions[9]);

    // 4th region
    m_Regions[3]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[3]->AddAdjacentRegion(m_Regions[5]);

    // 5th region
    m_Regions[4]->AddAdjacentRegion(m_Regions[1]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[5]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[7]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[8]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[4]->AddAdjacentRegion(m_Regions[2]);

    // 6th region
    m_Regions[5]->AddAdjacentRegion(m_Regions[3]);
    m_Regions[5]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[5]->AddAdjacentRegion(m_Regions[7]);

    // 7th region
    m_Regions[6]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[11]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[13]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[14]);
    m_Regions[6]->AddAdjacentRegion(m_Regions[0]);

    // 8th region
    m_Regions[7]->AddAdjacentRegion(m_Regions[5]);
    m_Regions[7]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[7]->AddAdjacentRegion(m_Regions[8]);

    // 9th region
    m_Regions[8]->AddAdjacentRegion(m_Regions[7]);
    m_Regions[8]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[8]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[8]->AddAdjacentRegion(m_Regions[12]);

    // 10th region
    m_Regions[9]->AddAdjacentRegion(m_Regions[2]);
    m_Regions[9]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[9]->AddAdjacentRegion(m_Regions[11]);

    // 11th region
    m_Regions[10]->AddAdjacentRegion(m_Regions[9]);
    m_Regions[10]->AddAdjacentRegion(m_Regions[2]);
    m_Regions[10]->AddAdjacentRegion(m_Regions[4]);
    m_Regions[10]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[10]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[10]->AddAdjacentRegion(m_Regions[11]);

    // 12th region
    m_Regions[11]->AddAdjacentRegion(m_Regions[9]);
    m_Regions[11]->AddAdjacentRegion(m_Regions[10]);
    m_Regions[11]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[11]->AddAdjacentRegion(m_Regions[13]);

    // 13th region
    m_Regions[12]->AddAdjacentRegion(m_Regions[8]);
    m_Regions[12]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[12]->AddAdjacentRegion(m_Regions[14]);

    // 14th region
    m_Regions[13]->AddAdjacentRegion(m_Regions[11]);
    m_Regions[13]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[13]->AddAdjacentRegion(m_Regions[14]);

    // 15th region
    m_Regions[14]->AddAdjacentRegion(m_Regions[13]);
    m_Regions[14]->AddAdjacentRegion(m_Regions[6]);
    m_Regions[14]->AddAdjacentRegion(m_Regions[0]);
    m_Regions[14]->AddAdjacentRegion(m_Regions[12]);
}

const std::vector<std::shared_ptr<Server::Region>> &Server::Map::GetRegions() const{
    return m_Regions;
}

std::vector<int> Server::Map::GetValidRegionToAttack(int userId) const {
    std::vector<int> validRegions;

    /* all regions that:
     * have neighbour owned by userId
     */

    for (const auto& region : m_Regions) {
        bool hasUserNeighbour = false;
        for (const auto& neighbour : region->GetAdjacentRegions()) {
            auto neighbourObj = neighbour.lock();
            if (neighbourObj->GetUserId() == userId) {
                hasUserNeighbour = true;
                continue;
            }
        }

        if (hasUserNeighbour)
            validRegions.push_back(region->GetId());
    }

    return validRegions;
}

std::shared_ptr<Server::Region> Server::Map::GetRegion(int id) const {
    return m_Regions[id];
}

std::vector<int> Server::Map::GetAvailableRegionsForPowerups(int userId) const
{
    std::vector<int> validRegions;
    for (const auto& region : m_Regions)
    {
        if(region->GetUserId() == userId && region->GetScore() >= 200)
            validRegions.push_back(region->GetId());
    }
    return validRegions;
}
