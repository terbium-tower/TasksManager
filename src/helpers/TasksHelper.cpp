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
	
	void addTask( TaskCallback callback, Thread type, float seconds )
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