#pragma once

#include <memory>
#include "Question.h"
#include "User.h"
#include "QuestionChoice.h"
#include "UserStatistics.h"
#include <sqlite_orm/sqlite_orm.h>

namespace DB
{
    using namespace sqlite_orm;

    namespace
    {
        inline auto Startup(const std::string& path)
        {
            return make_storage(path,
                                make_table("Question",
                                           make_column("ID_Question", &Question::SetId, &Question::GetId, 
                                                       primary_key(), autoincrement()),
                                           make_column("Question", &Question::SetQuestion, &Question::GetQuestion),
                                           make_column("Category", &Question::SetCategory, &Question::GetCategory),
                                           make_column("Type", &Question::SetType, &Question::GetType),
                                           make_column("Answer", &Question::SetAnswer, &Question::GetAnswer)),
                                make_table("QuestionChoice",
                                           make_column("ID_QuestionChoice", &QuestionChoice::SetId, &QuestionChoice::GetId,
                                                       primary_key(), autoincrement()),
                                           make_column("ID_Question", &QuestionChoice::SetQuestionId, &QuestionChoice::GetQuestionId,
                                                       foreign_key(&QuestionChoice::GetQuestionId).references(&Question::GetId)
                                                                                                  .on_delete.cascade()),
                                           make_column("Is_Correct", &QuestionChoice::SetIsCorrect, &QuestionChoice::GetIsCorrect),
                                           make_column("Choice", &QuestionChoice::SetChoice, &QuestionChoice::GetChoice)),
                                make_table("User",
                                           make_column("ID_User", &User::SetId, &User::GetId,
                                                      primary_key(), autoincrement()),
                                           make_column("Name", &User::SetName, &User::GetName),
                                           make_column("Password", &User::SetPassword, &User::GetPassword)),
                                make_table("UserStatistics",
                                           make_column("ID_UserStatistics", &UserStatistics::SetId, &UserStatistics::GetId,
                                                       primary_key(), autoincrement()),
                                           make_column("ID_User", &UserStatistics::SetUser, &UserStatistics::GetUserId,
                                                       foreign_key(&UserStatistics::GetUserId).references(&User::GetId)
                                                                                              .on_delete.cascade()),
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

        /// \brief Inserts an element into a table and returns the inserted id
        template <typename T>
        uint32_t Insert(const T& object);

        /// \brief Returns all elements from a table
        template <typename T>
        std::vector<T> GetAll();

        /// \brief Returns the element with the specific id from a table
        template <typename T>
        T Get(const uint32_t id);

        /// \brief Returns the users with the specific username from a table
        template <typename T>
        std::vector<T> GetUserByUsername(const std::string& username);

        /// \brief Returns the numeric questions from table
        template <typename T>
        std::vector<T> GetNumericQuestions();

        /// \brief Returns the number of elements inside a table
        template <typename T>
        uint32_t Count();

        /// \brief Replaces an existing element, ids must match
        template <typename T>
        void Replace(const T& object);

        /// \brief Removes an existing element from a table
        template <typename T>
        void Remove(const uint32_t id);

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

    template<typename T>
    inline uint32_t DBAccess::Insert(const T& object)
    {
        try
        {
            return storage.insert<T>(object);
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
        return uint32_t();
    }

    template<typename T>
    inline std::vector<T> DBAccess::GetAll()
    {
        try
        {
            return storage.get_all<T>();
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
        return std::vector<T>();
    }

    template<typename T>
    inline T DBAccess::Get(const uint32_t id)
    {
        try
        {
            return storage.get<T>(id);
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
        return T();
    }

    template<typename T>
    inline std::vector<T> DBAccess::GetUserByUsername(const std::string& username)
    {
        try
        {
            return storage.get_all<T>(where(c(&User::GetName) == username));
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
        return std::vector<T>();
    }

    template<typename T>
    inline uint32_t DBAccess::Count()
    {
        try
        {
           return storage.count<T>();
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unkown exception" << '\n';
        }
        return 0;
    }

    template<typename T>
    inline void DBAccess::Replace(const T& object)
    {
        try
        {
            storage.replace(object);
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "DBAccess::Replace fail" << '\n';
        }
    }

    template<typename T>
    inline void DBAccess::Remove(const uint32_t id)
    {
        try
        {
            storage.remove<T>(id);
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
    }

    template<typename T>
    std::vector<T> DBAccess::GetNumericQuestions() {
        try
        {
            return storage.get_all<T>(where(c(&Question::GetType) == "single_choice"));
        }
        catch (std::system_error& e)
        {
            std::cout << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "unknown exception" << '\n';
        }
        return std::vector<T>();
    }

}//namespace DB
