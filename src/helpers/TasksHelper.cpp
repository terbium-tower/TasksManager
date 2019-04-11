/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TasksHelper.h"

namespace ttower
{
	static std::shared_ptr<TasksManager> tasksMng;

	// Initialize function
	void initialize()
	{
		tasksMng = std::make_shared<TasksManager>();
	}
	
	// Tasks Functions
	void update( float dt )
	{
		if( !tasksMng )
		{
			TasksManagerLog( "Task Manager is not initialized!" );
			return;
		}

		tasksMng->update( dt );
	}
	
	void addTask( TaskCallback callback )
	{
		if( !tasksMng )
		{
			TasksManagerLog( "Task Manager is not initialized!" );
			return;
		}

		tasksMng->addTask( callback );
	}

	void addTimedTask( TaskCallback callback, ThreadType type, float seconds )
	{
		if( !tasksMng )
		{
			TasksManagerLog( "Task Manager is not initialized!" );
			return;
		}

		tasksMng->addTimedTask( callback, type, seconds );
	}
}

//std::shared_ptr<ttower::TasksManager> ttower::tasksMng = nullptr;