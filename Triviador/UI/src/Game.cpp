#include <Game.h>

void Game::SetNrPlayers(uint8_t nrPlayers)
{
	m_nrPlayers = nrPlayers;
}

uint8_t Game::GetNrPlayers()
{
	return m_nrPlayers;
}

void Game::ReadMap(int id)
{
	std::ifstream f;
	std::string mapPath;

	switch (id)
	{
	case 1:
		m_type = 9;
		m_nrPlayers = 2;
		mapPath = std::string(RESOURCE_DIR) + "/1.txt";
		break;
	case 2:
		m_type = 15;
		m_nrPlayers = 3;
		mapPath = std::string(RESOURCE_DIR) + "/2.txt";
		break;
	case 3:
		m_type = 24;
		m_nrPlayers = 4;
		mapPath = std::string(RESOURCE_DIR) + "/3.txt";
		break;
	default:
		break;
	}

	f.open(mapPath.data());
    m_map.clear();
	for (int i = 0;i <= m_type;i++)
	{
		auto x = std::make_shared<Region>(0, 0, i+1, false);
		std::vector<Tile> auxTile = {};
		m_tiles.push_back(auxTile);
		m_map.push_back(x);
	}

	std::vector<std::vector<int>> mat;

	// Interpret and populate the region.
	if (f.is_open())
	{
		int n;
		for (int i = 0; i < HEIGHT; i++)
		{
			mat.push_back({});
			for (int j = 0; j < WIDTH; j++)
			{
				f >> n;
				mat[i].push_back(n);

				for (int temp = 0; temp < m_map.size(); temp++)
					if (n == m_map[temp]->GetNumber())
					{
						Tile t;
						t.SetTile(std::make_pair(i, j), m_map[temp]);
						if (i == 0 || i == HEIGHT - 1)
							t.SetBorder();
						if (j == 0 || j == WIDTH - 1)
							t.SetBorder();
						m_tiles[n].push_back(t);
					}
				if (j != 0 && mat[i][j] != mat[i][j - 1])
				{
					for (int temp = 0; temp < m_map.size(); temp++)
						if (mat[i][j] == m_map[temp]->GetNumber())
						{
							for (int tem = 0; tem < m_map.size(); tem++)
								if (mat[i][j - 1] == m_map[tem]->GetNumber())
								{
									m_map[tem]->AddNeighbour(m_map[temp]);
									m_map[temp]->AddNeighbour(m_map[tem]);

									for (Tile& x : m_tiles[mat[i][j]])
									{
										if (x.GetCoordinate().first == i && x.GetCoordinate().second == j)
											x.SetBorder();
										if (x.GetCoordinate().first == i && x.GetCoordinate().second == j - 1)
											x.SetBorder();
									}
								}
						}
				}
				if (i != 0 && mat[i][j] != mat[i - 1][j])
				{
					for (int temp = 0; temp < m_map.size(); temp++)
						if (mat[i][j] == m_map[temp]->GetNumber())
						{
							for (int tem = 0; tem < m_map.size(); tem++)
								if (mat[i - 1][j] == m_map[tem]->GetNumber())
								{
									m_map[tem]->AddNeighbour(m_map[temp]);
									m_map[temp]->AddNeighbour(m_map[tem]);
									for (Tile& x : m_tiles[mat[i][j]])
									{
										if (x.GetCoordinate().first == i && x.GetCoordinate().second == j)
											x.SetBorder();
										if (x.GetCoordinate().first == i - 1 && x.GetCoordinate().second == j)
											x.SetBorder();
									}
								}
						}
				}
			}
		}

		for (int i = 0; i < m_type; i++)
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
		std::cout << "Region " << i << " tiles:\n";
		for (int j = 0;j < m_tiles[i].size();j++)
			std::cout << m_tiles[i][j].GetCoordinate().first << " " << m_tiles[i][j].GetCoordinate().second << std::endl;
	}
}

uint8_t Game::getType()
{
	return m_type;
}

void Game::setType(uint8_t type)
{
	m_type = type;
}

std::vector<std::shared_ptr<Region>> Game::getMap()
{
	return m_map;
}

std::vector<std::vector<Tile>> Game::getTiles()
{
	return m_tiles;
}

void Game::selectRegions(const std::vector<int>& regions)
{

	for (const int& region : regions)
    {
        m_map[region - 1]->SetHighlight();
	}
}

void Game::UpdateMap(const std::vector<Region>& regions)
{
    for(const auto& region : regions)
    {
        m_map[region.GetNumber() - 1]->SetUserId(region.GetUserId());
        m_map[region.GetNumber() - 1]->SetBase(region.IsBase());
        m_map[region.GetNumber() - 1]->SetValue(region.GetValue());

    }
}
