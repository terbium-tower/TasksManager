/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TManager.h"
#include <future>
#include <ppltasks.h>
#include <agents.h>

namespace ttower
{
	// Realization
	TasksManager::TasksManager()
		: m_timedTasksCount( 0ull )
	{

	}
	
	void TasksManager::addTask( TaskCallback callback )
	{
		m_tasks.push_back( Task( callback ) );
	}

	void TasksManager::addTimedTask( TaskCallback callback, ThreadType type, float seconds )
	{
		TimedTasks& timedTasks = m_timedTasks[(short)type];
		std::uint64_t newId = m_timedTasksCount;

		switch( type )
		{
			case ThreadType::MainThread:
			{
				timedTasks.insert( { newId, TimedTask( newId, callback, seconds ) } );

				break;
			}

			case ThreadType::NewThread:
			{
				timedTasks.insert( { newId, TimedTask( newId, callback, seconds ) } );
				std::uint64_t milliseconds = static_cast<std::uint64_t>( seconds * 1000.0f );

				std::shared_ptr<TasksManager> tasksMng = shared_from_this();
				std::weak_ptr<TasksManager> weakMng = tasksMng;
				
				concurrency::task_completion_event<void> tce;
				auto fire_once = new concurrency::timer<int>( milliseconds, 0, nullptr, false );
				auto callback = new concurrency::call<int>(
					[tce, milliseconds, newId, type, weakMng](int)
				{
					std::shared_ptr<TasksManager> mng = weakMng.lock();
					if( !mng )
						return;
					
					TimedTasks& timedTasks = mng->m_timedTasks[(short)type];
					if( timedTasks.count( newId ) )
					{
						timedTasks.at( newId ).callback();
						timedTasks.unsafe_erase( newId );
					}
					
					tce.set();
				});

				fire_once->link_target(callback);
				fire_once->start();

				concurrency::task<void> event_set(tce);
				event_set.then([callback, fire_once]()
				{
					delete callback;
					delete fire_once;
				});

				break;
			}
		}
		
		m_timedTasksCount++;
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
		TimedTasks& timedTasks = m_timedTasks[(short)ThreadType::MainThread];

		TimedTasks::iterator it = timedTasks.begin();
		TimedTasks::iterator end = timedTasks.end();

		for( ;it != end; )
		{
			if( it->second.seconds <= 0.0f )
			{
				it->second.callback();
				it = timedTasks.unsafe_erase( it );
				end = timedTasks.end();
			}
			else
			{
				it->second.seconds -= dt;
				++it;
			}			
		}
	}
}