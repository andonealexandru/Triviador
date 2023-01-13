#include "PlayerService.h"

Server::PlayerService &Server::PlayerService::GetInstance() {
    static PlayerService instance;
    return instance;
}
