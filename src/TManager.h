/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <vector>
#include "TaskConstants.h"

namespace ttower
{
	// Initialize function
	void initialize();

	class TasksManager
	{

	public:

		TasksManager();

		void addTask( TaskCallback callback, TaskType type );
		void addTimedTask( TaskCallback callback, TaskType type );

	private:

		std::vector< Task > m_tasks;
	};
}