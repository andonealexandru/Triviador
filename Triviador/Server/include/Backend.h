#pragma once

#include "crow.h"

namespace Server
{
	
	class Backend
	{
	public:

		Backend();

	private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

	};
}