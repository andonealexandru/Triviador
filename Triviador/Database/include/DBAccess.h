#pragma once

#include <memory>
#include <Question.h>
#include <User.h>
#include <QuestionChoice.h>
#include <sqlite_orm/sqlite_orm.h>
using namespace sqlite_orm;

namespace DB
{
	class DBAccess
	{
	public:
		/// \brief  Returns (the one and only) instance of DBAccess.
		static DBAccess* GetInstance();

		/// \brief Deletes (the one and only) instance of DBAccess.
		static void DestroyInstance();

		~DBAccess() = default;

        /// \brief Initializes the database
        static auto& Startup()
        {
            static auto storage = make_storage("../Questions.db",
                                               make_table("Question",
                                                          make_column("ID_Question", &Question::m_id, primary_key()),
                                                          make_column("Question", &Question::m_question),
                                                          make_column("Category", &Question::m_category),
                                                          make_column("Type", &Question::m_type),
                                                          make_column("Answer", &Question::m_answer)),
                                               make_table("QuestionChoice",
                                                          make_column("ID_QuestionChoice", &QuestionChoice::m_id, primary_key()),
                                                          make_column("ID_Question", &QuestionChoice::m_id),
                                                          foreign_key(&QuestionChoice::m_id).references(&Question::m_id),
                                                          make_column("IsCorrect", &QuestionChoice::m_isCorect),
                                                          make_column("Choice", &QuestionChoice::m_choice))
                                               );
            return storage;
        }


	private:
        /// \brief Private constructor. DBAccess object gets obtained by GetInstance() call.
		DBAccess() = default;

		DBAccess(DBAccess&&) = delete;
		DBAccess(const DBAccess&) = delete;
		DBAccess& operator=(DBAccess&&) = delete;
		DBAccess& operator=(const DBAccess&) = delete;

		/// \brief the (one and only) instance of DBAccess.
		static std::unique_ptr<DBAccess> m_instance;
	};

}//namespace DB
