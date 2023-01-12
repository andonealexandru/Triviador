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
        Player(int id, int userId, Status status);
        Player(const Player& other);
        Player &operator=(const Player& other);

        ~Player() = default;

        // getters
        int GetId() const;
        Status GetStatus() const;
        std::shared_ptr<DB::User> GetUser() const;

        // setters
        void SetId(int id);
        void SetStatus(Status status);
        void SetUser(int userId);

    private:
        int m_id;
        std::shared_ptr<DB::User> m_user;
        Status m_status;
    };
}