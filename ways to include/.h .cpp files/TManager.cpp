/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TManager.h"
#include <ppltasks.h>
#include <agents.h>

namespace ttower
{
	// Realization
	TasksManager::TasksManager()
	{

	}
	
	void TasksManager::addTask( TaskCallback callback, Thread type )
	{
		switch( type )
		{
			case Thread::MainThread: m_tasks.push_back( Task( callback ) ); break;
			case Thread::NewThread: addTimedTask( callback, type, 0.0f ); break;
		}
	}

	void TasksManager::addTimedTask( TaskCallback callback, Thread type, float seconds )
	{
		TimedTasks& timedTasks = m_timedTasks;

		switch( type )
		{
			case Thread::MainThread: timedTasks.push_back( { TimedTask( callback, seconds ) } ); break;
			case Thread::NewThread:
			{
				std::uint64_t milliseconds = static_cast<std::uint64_t>( seconds * 1000.0f );

				concurrency::task_completion_event<void> tce;
				auto fire_once = new concurrency::timer<int>( milliseconds, 0, nullptr, false );
				auto target = new concurrency::call<int>(
					[tce, callback](int)
				{
					callback();
					tce.set();
				});

				fire_once->link_target(target);
				fire_once->start();

				concurrency::task<void> event_set(tce);
				event_set.then([target, fire_once]()
				{
					delete target;
					delete fire_once;
				});

				break;
			}
		}
	}
	
	void TasksManager::update( float dt )
	{
		// Tasks
		while( !m_tasks.empty() )
		{
			m_tasks.front().callback();
			m_tasks.pop_front();
		}

		// Timed Tasks
		TimedTasks::iterator it = m_timedTasks.begin();
		TimedTasks::iterator end = m_timedTasks.end();

		for( ;it != end; )
		{
			if( it->seconds <= 0.0f )
			{
				it->callback();
				it = m_timedTasks.erase( it );
				end = m_timedTasks.end();
			}
			else
			{
				it->seconds -= dt;
				++it;
			}			
		}
	}
}