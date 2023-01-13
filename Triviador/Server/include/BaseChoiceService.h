#ifndef TRIVIADOR_BASECHOICESERVICE_H
#define TRIVIADOR_BASECHOICESERVICE_H

#include "crow.h"

#include "DBAccess.h"
#include "Status.h"
#include "Map.h"

namespace Server {
    class BaseChoiceService {
    public:
        BaseChoiceService(crow::SimpleApp &app);

    private:

    };
}

#endif //TRIVIADOR_BASECHOICESERVICE_H
