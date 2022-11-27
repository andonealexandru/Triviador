#include <DBAccess.h>

namespace DB
{
	std::shared_ptr<DBAccess> DBAccess::m_instance;

	DBAccess* DBAccess::GetInstance()
	{
		if (!m_instance)
		{
			m_instance.reset(new DBAccess());
		}
		return m_instance.get();
	}

	void DBAccess::DestroyInstance()
	{
		m_instance.reset();
	}

    DBAccess::DBAccess() : storage(Startup())
    {
    }

    Storage DBAccess::GetStorage() const
    {
        return storage;
    }

}//namespace DB