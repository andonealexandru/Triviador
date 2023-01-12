#ifndef TRIVIADOR_STATUS_H
#define TRIVIADOR_STATUS_H

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
    };
}

#endif //TRIVIADOR_STATUS_H
