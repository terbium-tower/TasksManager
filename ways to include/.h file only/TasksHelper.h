/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <vector>
#include <list>
#include <memory>
#include <ppltasks.h>
#include <agents.h>

namespace ttower
{
	// Constants
	const int kInitializeTasksReserve = 100;

	// Typedefs 
	using TaskCallback = std::function< void() >;

	// Enums
	enum class Thread : short
	{
		None = 0,
		MainThread,
		NewThread,
		MAX
	};

	// Structs
	struct Task
	{
		Task( TaskCallback _callback = NULL )
			: callback( _callback )
		{}

		TaskCallback callback;
	};
	
	struct TimedTask
	{
		TimedTask( TaskCallback _callback = NULL,
				   float _seconds = 0.0f )
			: callback( _callback )
			, seconds( _seconds )
		{}

		TaskCallback callback;
		float seconds;
	};
	
	// Functions
	inline void TasksManagerLog( const std::string& str )
	{
		printf( "%s", str.c_str() );
	}

	using Tasks = std::list< Task >;
	using TimedTasks = std::vector< TimedTask >;

	class TasksManager
		: public std::enable_shared_from_this< TasksManager >
	{

	public:

		TasksManager()
		{}

		void addTask( TaskCallback callback, Thread type )
		{
			switch( type )
			{
				case Thread::MainThread: m_tasks.push_back( Task( callback ) ); break;
				case Thread::NewThread: addTimedTask( callback, type, 0.0f ); break;
			}
		}

		void addTimedTask( TaskCallback callback, Thread type, float seconds )
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

		void update( float dt )
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

	private:
		
		Tasks m_tasks;
		TimedTasks m_timedTasks;
	};
		
	static std::shared_ptr<TasksManager> tasksMng;

	// Initialize function
	inline void initialize()
	{
		tasksMng = std::make_shared<TasksManager>();
	}
	
	// Tasks Functions
	inline void update( float dt )
	{
		if( !tasksMng )
		{
			TasksManagerLog( "Task Manager is not initialized!" );
			return;
		}

		tasksMng->update( dt );
	}
	
	inline void addTask( TaskCallback callback, Thread type, float seconds )
	{
		if( !tasksMng )
		{
			TasksManagerLog( "Task Manager is not initialized!" );
			return;
		}
		
		if( seconds != 0.0f )
			tasksMng->addTimedTask( callback, type, seconds );
		else
			tasksMng->addTask( callback, type );
	}
}