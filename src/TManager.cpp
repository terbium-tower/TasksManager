/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TManager.h"

namespace ttower
{
	static const TasksManager* tasksMng = nullptr;

	// Initialize function
	void initialize()
	{
		tasksMng = new TasksManager();
	}
	
	// Realization
	TasksManager::TasksManager()
	{
		m_tasks.reserve( kInitializeTasksReserve );
	}
}