#pragma once

#include <memory>
#include <Question.h>
#include <User.h>
#include <QuestionChoice.h>
#include <UserStatistics.h>
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

namespace DB
{
    namespace
    {
        inline auto Startup(std::string path)//adauga parametru calea .sqlite
        {
            return make_storage(path,
                                make_table("Question",
                                           make_column("ID_Question", &Question::SetId, &Question::GetId, primary_key()),
                                           make_column("Question", &Question::SetQuestion, &Question::GetQuestion),
                                           make_column("Category", &Question::SetQuestion, &Question::GetQuestion),
                                           make_column("Type", &Question::SetType, &Question::GetType),
                                           make_column("Answer", &Question::SetAnswer, &Question::GetAnswer)),
                                make_table("QuestionChoice",
                                           make_column("ID_QuestionChoice", &QuestionChoice::SetId, &QuestionChoice::GetId, primary_key()),
                                           make_column("ID_Question", &QuestionChoice::SetQuestionId, &QuestionChoice::GetQuestionId,
                                                       foreign_key(&QuestionChoice::GetQuestionId).references(&Question::GetId)),
                                           make_column("IsCorrect", &QuestionChoice::SetIsCorrect, &QuestionChoice::GetIsCorrect),
                                           make_column("Choice", &QuestionChoice::SetChoice, &QuestionChoice::GetChoice)),
                                make_table("User",
                                           make_column("ID_User", &User::SetId, &User::GetId, primary_key()),
                                           make_column("Username", &User::SetName, &User::GetName),
                                           make_column("Password", &User::SetPassword, &User::GetPassword)),
                                make_table("UserStatistics",
                                           make_column("ID_UserStatistics", &UserStatistics::SetId, &UserStatistics::GetId, primary_key()),
                                           make_column("ID_User", &UserStatistics::SetUser, &UserStatistics::GetUserId,
                                                       foreign_key(&UserStatistics::GetUserId).references(&User::GetId)),
                                           make_column("Game_Count", &UserStatistics::SetGameCount, &UserStatistics::GetGameCount),
                                           make_column("Won_Games", &UserStatistics::SetWonGames, &UserStatistics::GetWonGames))
            );
        }
        using Storage = decltype(Startup(""));
    }

	class DBAccess
	{
	public:
		static DBAccess* GetInstance();

		static void DestroyInstance();
		~DBAccess() = default;

        Storage GetStorage() const;
	private:
		DBAccess();

		DBAccess(DBAccess&&) = delete;
		DBAccess(const DBAccess&) = delete;
		DBAccess& operator=(DBAccess&&) = delete;
		DBAccess& operator=(const DBAccess&) = delete;

		static std::shared_ptr<DBAccess> m_instance;
        Storage storage;// = Startup("cale valida catre sqlite");
	};

}//namespace DB
