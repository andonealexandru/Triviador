#pragma once
#include <cstdint>
#include "UserStatistics.h"

class Game
{
public:
	// constructors
	Game();
	Game(UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics);
	Game(UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics, uint8_t length);
	Game(uint8_t id, UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics, uint8_t length);
	Game(const Game& other);
	Game& operator=(const Game& other);

	// getters
	uint8_t GetId();
	UserStatistics* getFirstUserStatistics();
	UserStatistics* getSecondUserStatistics();
	uint8_t GetLength();

	// setters
	void SetId(uint8_t id);
	void SetFirstUserStatistics(UserStatistics* userStatistics);
	void SetSecondUserStatistics(UserStatistics* userStatistics);
	void SetLength(uint8_t length);
		
private:
	uint8_t mId;
	std::pair<UserStatistics*, UserStatistics*> mUserStatistics;
	uint8_t mLength;
};

