/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TaskConstants.h"

namespace ttower
{
	using Tasks = std::list< Task >;
	using TimedTasks = std::vector< TimedTask >;

	class TasksManager
		: public std::enable_shared_from_this< TasksManager >
	{

	public:

		TasksManager();

		void addTask( TaskCallback callback, Thread type );
		void addTimedTask( TaskCallback callback, Thread type, float seconds );

		void update( float dt );

	private:
		
		Tasks m_tasks;
		TimedTasks m_timedTasks;
	};
}