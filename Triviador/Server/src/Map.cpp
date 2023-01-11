#include "Map.h"

#include <vector>

int Server::Map::GetId() {
    return m_Id;
}

void Server::Map::GenerateThreePlayerMap() {
    m_Id = 2;
    m_Regions.resize(15);

    for (int i = 0; i < 15; i++)
        m_Regions[i].SetId(i+1);

    // 1st region
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[8]));
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[12]));
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[14]));
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[6]));
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[0].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));

    // 2nd region
    m_Regions[1].AddAdjacentRegion(std::make_shared<Region>(m_Regions[2]));
    m_Regions[1].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[1].AddAdjacentRegion(std::make_shared<Region>(m_Regions[3]));

    // 3rd region
    m_Regions[2].AddAdjacentRegion(std::make_shared<Region>(m_Regions[1]));
    m_Regions[2].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[2].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[2].AddAdjacentRegion(std::make_shared<Region>(m_Regions[9]));

    // 4th region
    m_Regions[3].AddAdjacentRegion(std::make_shared<Region>(m_Regions[1]));
    m_Regions[3].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[3].AddAdjacentRegion(std::make_shared<Region>(m_Regions[5]));

    // 5th region
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[1]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[3]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[5]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[7]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[8]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[4].AddAdjacentRegion(std::make_shared<Region>(m_Regions[2]));

    // 6th region
    m_Regions[5].AddAdjacentRegion(std::make_shared<Region>(m_Regions[3]));
    m_Regions[5].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[5].AddAdjacentRegion(std::make_shared<Region>(m_Regions[7]));

    // 7th region
    m_Regions[6].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[6].AddAdjacentRegion(std::make_shared<Region>(m_Regions[11]));
    m_Regions[6].AddAdjacentRegion(std::make_shared<Region>(m_Regions[13]));
    m_Regions[6].AddAdjacentRegion(std::make_shared<Region>(m_Regions[14]));
    m_Regions[6].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));

    // 8th region
    m_Regions[7].AddAdjacentRegion(std::make_shared<Region>(m_Regions[5]));
    m_Regions[7].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[7].AddAdjacentRegion(std::make_shared<Region>(m_Regions[8]));

    // 9th region
    m_Regions[8].AddAdjacentRegion(std::make_shared<Region>(m_Regions[7]));
    m_Regions[8].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[8].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));
    m_Regions[8].AddAdjacentRegion(std::make_shared<Region>(m_Regions[12]));

    // 10th region
    m_Regions[9].AddAdjacentRegion(std::make_shared<Region>(m_Regions[2]));
    m_Regions[9].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[9].AddAdjacentRegion(std::make_shared<Region>(m_Regions[11]));

    // 11th region
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[9]));
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[2]));
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[4]));
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[6]));
    m_Regions[10].AddAdjacentRegion(std::make_shared<Region>(m_Regions[11]));

    // 12th region
    m_Regions[11].AddAdjacentRegion(std::make_shared<Region>(m_Regions[9]));
    m_Regions[11].AddAdjacentRegion(std::make_shared<Region>(m_Regions[10]));
    m_Regions[11].AddAdjacentRegion(std::make_shared<Region>(m_Regions[6]));
    m_Regions[11].AddAdjacentRegion(std::make_shared<Region>(m_Regions[13]));

    // 13th region
    m_Regions[12].AddAdjacentRegion(std::make_shared<Region>(m_Regions[8]));
    m_Regions[12].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));
    m_Regions[12].AddAdjacentRegion(std::make_shared<Region>(m_Regions[14]));

    // 14th region
    m_Regions[13].AddAdjacentRegion(std::make_shared<Region>(m_Regions[11]));
    m_Regions[13].AddAdjacentRegion(std::make_shared<Region>(m_Regions[6]));
    m_Regions[13].AddAdjacentRegion(std::make_shared<Region>(m_Regions[14]));

    // 15th region
    m_Regions[14].AddAdjacentRegion(std::make_shared<Region>(m_Regions[13]));
    m_Regions[14].AddAdjacentRegion(std::make_shared<Region>(m_Regions[6]));
    m_Regions[14].AddAdjacentRegion(std::make_shared<Region>(m_Regions[0]));
    m_Regions[14].AddAdjacentRegion(std::make_shared<Region>(m_Regions[12]));
}

std::vector<Region> &Server::Map::GetRegions() {
    return m_Regions;
}
