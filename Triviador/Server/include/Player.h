#pragma once

#include <memory>
#include <string>

namespace Server {
    class Player
    {
    public:
        // constructors
        Player(int id, const std::string& name);

        ~Player() = default;

        // getters
        int GetId() const;
        const std::string& GetName() const;

        // setters
        void SetId(int id);
        void SetName(const std::string& name);

    private:
        int m_id;
        std::string m_name;
    };
}