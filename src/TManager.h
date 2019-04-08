// Author: Eugene Fomin
#pragma once

// Includes
#include <functional>

namespace ttower
{
	class TasksManager
	{
	public:

		void addTask( std::function< void() > callback );
	};
}