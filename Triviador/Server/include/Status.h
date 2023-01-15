#ifndef TRIVIADOR_STATUS_H
#define TRIVIADOR_STATUS_H

#include <string>

namespace Server {
    enum Status {
        InLobby,
        PlayersModified,
        InGame,
        StartNewGame,
        FirstQuestion,
        BaseChoice,
        RegionQuestion,
        RegionChoice,
        WaitingForAnswers,
        MapChanged,
        Answer,
        AllPlayersAnswered,
        Duel,
        AttackQuestion,
        PowerupRegionChoice,
    };

    inline std::string ToString(Status status) { // TODO: best approach?
        switch (status) {
            case Status::InLobby: return "InLobby";
            case Status::BaseChoice: return "BaseChoice";
            case Status::FirstQuestion: return "FirstQuestion";
            case Status::InGame: return "InGame";
            case Status::RegionChoice: return "RegionChoice";
            case Status::RegionQuestion: return "RegionQuestion";
            case Status::PlayersModified: return "PlayersModified";
            case Status::StartNewGame: return "StartNewGame";
            case Status::WaitingForAnswers: return "WaitingForAnswers";
            case Status::MapChanged: return "MapChanged";
            case Status::Answer: return "Answer";
            case Status::AllPlayersAnswered: return "AllPlayersAnswered";
            case Status::Duel: return "Duel";
            default: return "Unknown";
        }
    }
}

#endif //TRIVIADOR_STATUS_H
