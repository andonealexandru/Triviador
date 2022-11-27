#pragma once

#include <memory>
#include <QuestionService.h>
#include <UserService.h>
#include <QuestionChoiceService.h>
#include <UserStatisticsService.h>
#include <GameService.h>
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

namespace DB
{
    namespace
    {
        inline auto Startup()
        {
            return make_storage("../Questions.db",
                                make_table("Question",
                                           make_column("ID_Question", &QuestionService::SetId, &QuestionService::GetId, primary_key()),
                                           make_column("Question", &QuestionService::SetQuestion, &QuestionService::GetQuestion),
                                           make_column("Category", &QuestionService::SetQuestion, &QuestionService::GetQuestion),
                                           make_column("Type", &QuestionService::SetType, &QuestionService::GetType),
                                           make_column("Answer", &QuestionService::SetAnswer, &QuestionService::GetAnswer)),
                                make_table("QuestionChoice",
                                           make_column("ID_QuestionChoice", &QuestionChoiceService::SetId, &QuestionChoiceService::GetId, autoincrement(), primary_key()),
                                           make_column("ID_Question", &QuestionChoiceService::SetQuestionId, &QuestionChoiceService::GetQuestionId,
                                                       foreign_key(&QuestionChoiceService::SetQuestionId).references(&QuestionService::GetId)),
                                           make_column("IsCorrect", &QuestionChoiceService::SetIsCorrect, &QuestionChoiceService::GetIsCorrect),
                                           make_column("Choice", &QuestionChoiceService::SetChoice, &QuestionChoiceService::GetChoice)),
                                make_table("User",
                                           make_column("ID_User", &UserService::SetId, &UserService::GetId, autoincrement(), primary_key()),
                                           make_column("Username", &UserService::SetName, &UserService::GetName)),
                                make_table("UserStatistics",
                                           make_column("ID_UserStatistics", &UserStatisticsService::SetId, &UserStatisticsService::GetId, primary_key()),
                                           make_column("ID_User", &UserStatisticsService::SetUser, &UserStatisticsService::GetUserId,
                                                       foreign_key(&UserStatisticsService::SetUser).references(&UserService::GetId)),
                                           make_column("Score", &UserStatisticsService::SetScore, &UserStatisticsService::GetScore),
                                           make_column("Teritories", &UserStatisticsService::SetTerritoryCount, &UserStatisticsService::GetTerritoryCount)),
                                make_table("Game",
                                            make_column("ID_Game", &GameService::SetId, &GameService::GetId, autoincrement(), primary_key()),
                                            make_column("ID_UserStatistics1", &GameService::SetFirstUserStatistics, &GameService::GetFirstUserStatistics,
                                                        foreign_key(&GameService::SetFirstUserStatistics).references(&UserStatisticsService::GetId)),
                                            make_column("ID_UserStatistics2", &GameService::SetSecondUserStatistics, &GameService::GetSecondUserStatistics,
                                                        foreign_key(&GameService::SetFirstUserStatistics).references(&UserStatisticsService::GetId)),
                                            make_column("GameLenght", &GameService::SetLength, &GameService::GetLength))
            );
        }
        using Storage = decltype(Startup());
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
        Storage storage;
	};

}//namespace DB
