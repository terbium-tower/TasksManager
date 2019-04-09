/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TManager.h"

namespace ttower
{
	// Realization
	TasksManager::TasksManager()
	{

	}
	
	void TasksManager::update( float dt )
	{
		// Tasks
		Tasks& tasks = m_tasks[(short)TaskType::MainThread];
		TimedTasks& timedTasks = m_timedTasks[(short)TaskType::MainThread];

		while( !tasks.empty() )
		{
			tasks.front().callback();
			tasks.pop_front();
		}

		// Timed Tasks
		TimedTasks::iterator it = timedTasks.begin();
		TimedTasks::iterator end = timedTasks.end();

		for( ;it != end; )
		{
			
		}
	}
}