#include "Triviador.h"
#include <iostream>
#include <crow.h>
#include "DBAccess.h"
int main()
{
    auto storage = DB::DBAccess::GetInstance()->GetStorage();
    std::cout << storage.count<DB::Question>();

    return 0;
}

