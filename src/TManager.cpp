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
	
	void TasksManager::addTask( TaskCallback callback, TaskType type )
	{
		Tasks& tasks = m_tasks[(short)type];

		switch( type )
		{
			case TaskType::MainThread:
			{
				tasks.push_back( Task( callback ) );
				break;
			}

			case TaskType::NewThread:
			{
				break;
			}
		}
	}

	void TasksManager::addTimedTask( TaskCallback callback, TaskType type, float seconds )
	{
		TimedTasks& timedTasks = m_timedTasks[(short)type];

		switch( type )
		{
			case TaskType::MainThread:
			{
				timedTasks.push_back( TimedTask( callback, seconds ) );
				break;
			}

			case TaskType::NewThread:
			{
				break;
			}
		}
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
			if( it->seconds <= 0.0f )
			{
				it->callback();
				it = timedTasks.erase( it );
				end = timedTasks.end();
			}
			else
			{
				it->seconds -= dt;
				++it;
			}			
		}
	}
}