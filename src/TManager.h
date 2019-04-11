/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <memory>
#include <queue>
#include <concurrent_vector.h>
#include <concurrent_unordered_map.h>

#include "TaskConstants.h"

namespace ttower
{
	using Tasks = std::list< Task >;
	using TimedTasks = concurrency::concurrent_unordered_map< std::uint64_t, TimedTask >;

	class TasksManager
		: public std::enable_shared_from_this< TasksManager >
	{

	public:

		TasksManager();

		void addTask( TaskCallback callback );
		void addTimedTask( TaskCallback callback, ThreadType type, float milliseconds );

		void update( float dt );

	private:
		
		Tasks m_tasks;
		TimedTasks m_timedTasks[(short)ThreadType::MAX];
		std::uint64_t m_timedTasksCount;
	};
}