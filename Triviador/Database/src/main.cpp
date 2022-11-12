#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <string>
using namespace std;
using namespace sqlite_orm;
struct User{
    int id;
    std::string firstName;
    std::string lastName;
    int birthDate;
    std::unique_ptr<std::string> imageUrl;
    int typeId;
};
int main()
{
    auto storage = make_storage("db.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, autoincrement(), primary_key()),
                                           make_column("first_name", &User::firstName),
                                           make_column("last_name", &User::lastName),
                                           make_column("birth_date", &User::birthDate),
                                           make_column("image_url", &User::imageUrl),
                                           make_column("type_id", &User::typeId)));
    std::cout << "hi!\n";
    return 0;
}
