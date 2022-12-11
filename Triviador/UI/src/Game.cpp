#include <Game.h>

void Game::ReadMap()
{
    std::ifstream f;
    f.open("map.txt");
    m_type = 4; //TODO: change when map is ready
    for (int i = 0;i <= m_type;i++)
    {
        auto x = std::make_shared<Region>(0,1,i);
        std::vector<Tile> auxTile = {};
        m_tiles.push_back(auxTile);
        m_map.push_back(x);
    }

    std::vector<std::vector<int>> mat;
    if (f.is_open())
    {
        int n;
        Tile t;
        for (int i = 0;i < HEIGHT;i++)
        {
            mat.push_back({});
            for (int j = 0;j < WIDTH;j++)
            {
                f >> n;
                mat[i].push_back(n);
                
                for(int temp=0;temp<m_map.size();temp++)
                    if (n == m_map[temp]->GetNumber())
                    {
                        t.SetTile(std::make_pair(i, j), m_map[temp]);
                        m_tiles[n].push_back(t);
                    }
                if (j != 0 && mat[i][j] != mat[i][j - 1])
                {
                    for (int temp = 0;temp < m_map.size();temp++)
                        if (mat[i][j] == m_map[temp]->GetNumber())
                        {
                            for(int tem=0;tem<m_map.size();tem++)
                                if (mat[i][j - 1] == m_map[tem]->GetNumber())
                                {
                                    m_map[tem]->AddNeighbour(m_map[temp]);
                                    m_map[temp]->AddNeighbour(m_map[tem]);
                                }
                        }
                }
                if (i != 0 && mat[i][j] != mat[i-1][j])
                {
                    for (int temp = 0;temp < m_map.size();temp++)
                        if (mat[i][j] == m_map[temp]->GetNumber())
                        {
                            for (int tem = 0;tem < m_map.size();tem++)
                                if (mat[i-1][j] == m_map[tem]->GetNumber())
                                {
                                    m_map[tem]->AddNeighbour(m_map[temp]);
                                    m_map[temp]->AddNeighbour(m_map[tem]);
                                }
                        }
                }
            }
    }

        for (int i = 1;i <=m_type;i++)
        {
            int a, b;
            f >> a >> b;
            m_map[i]->SetCenter(std::make_pair(a, b));
        }

        f.close();
    }
    else
        std::cout << "Nu s-a putut deschide fisierul";
}

void Game::PrintMap() const
{
    std::cout << "Citirea:\n";
    for (int i = 0;i < m_map.size();i++)
    {
        m_map[i]->PrintRegion();
    }
}

void Game::PrintTiles() const
{
    for (int i = 0;i < m_tiles.size();i++)
    {
        std::cout << "Region "<<i<<" tiles:\n";
        for (int j = 0;j < m_tiles[i].size();j++)
            std::cout << m_tiles[i][j].GetCoordinate().first << " " << m_tiles[i][j].GetCoordinate().second << std::endl;
    }
}
