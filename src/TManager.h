/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <list>
#include <string>
#include "TaskConstants.h"

namespace ttower
{
	using Tasks = std::list< Task >;
	using TimedTasks = std::list< TimedTask >;

	class TasksManager
	{

	public:

		TasksManager();

		void addTask( TaskCallback callback, TaskType type );
		void addTimedTask( TaskCallback callback, TaskType type, float seconds );

		void update( float dt );

	private:
		
		Tasks m_tasks[(short)TaskType::MAX];
		TimedTasks m_timedTasks[(short)TaskType::MAX];
	};
}