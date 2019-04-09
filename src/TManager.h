/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <list>
#include "TaskConstants.h"

namespace ttower
{
	using Tasks = std::list< Task >;
	using TimedTasks = std::list< TimedTask >;

	class TasksManager
	{

	public:

		TasksManager();

		void addMainThreadTask( TaskCallback callback );
		void addTimedMainThreadTask( TaskCallback callback, std::uint64_t seconds );

		void update( float dt );

	private:
		
		Tasks m_tasks[(short)TaskType::MAX];
		TimedTasks m_timedTasks[(short)TaskType::MAX];
	};
}