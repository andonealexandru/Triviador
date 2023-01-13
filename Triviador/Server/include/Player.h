#pragma once

#include <memory>
#include <string>
#include <crow.h>

#include "DBAccess.h"
#include "Status.h"
#include "User.h"

namespace Server {
    class Player
    {
    public:
        // constructors
        Player() = default;
        Player(int id, int userId, int score, Status status);
        Player(const Player& other);
        Player &operator=(const Player& other);

        ~Player() = default;

        // getters
        int GetId() const;
        Status GetStatus() const;
        int GetScore() const;
        std::shared_ptr<DB::User> GetUser() const;

        // setters
        void SetId(int id);
        void SetStatus(Status status);
        void SetScore(int score);
        void SetUser(int userId);

        void IncrementScore();
        void DecrementScore();

    private:
        int m_id;
        int m_score;
        std::shared_ptr<DB::User> m_user;
        Status m_status;
    };
}