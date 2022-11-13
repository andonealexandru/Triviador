#include "Game.h"

Game::Game()
	: mId(0), mUserStatistics(std::make_pair(nullptr, nullptr)), mLength(0)
{}

Game::Game(UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics)
	: mId(0), mUserStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), mLength(0)
{}

Game::Game(UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics, uint8_t length)
	: mId(0), mUserStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), mLength(length)
{}

Game::Game(uint8_t id, UserStatistics* firstUserStatistics, UserStatistics* secondUserStatistics, uint8_t length)
	: mId(id), mUserStatistics(std::make_pair(firstUserStatistics, secondUserStatistics)), mLength(length)
{}

Game::Game(const Game& other)
	: mId(other.mId), mUserStatistics(std::make_pair(other.mUserStatistics.first, other.mUserStatistics.second)), mLength(other.mLength)
{}

Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		mId = other.mId;
		mUserStatistics = std::make_pair(other.mUserStatistics.first, other.mUserStatistics.second);
		mLength = other.mLength;
	}
	return *this;
}

uint8_t Game::GetId()
{
	return mId;
}

UserStatistics* Game::GetFirstUserStatistics()
{
	return mUserStatistics.first;
}

UserStatistics* Game::GetSecondUserStatistics()
{
	return mUserStatistics.second;
}

uint8_t Game::GetLength()
{
	return mLength;
}

void Game::SetId(uint8_t id)
{
	mId = id;
}

void Game::SetFirstUserStatistics(UserStatistics* userStatistics)
{
	mUserStatistics.first = userStatistics;
}

void Game::SetSecondUserStatistics(UserStatistics* userStatistics)
{
	mUserStatistics.second = userStatistics;
}

void Game::SetLength(uint8_t length)
{
	mLength = length;
}
