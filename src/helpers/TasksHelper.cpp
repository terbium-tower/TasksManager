/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "TasksHelper.h"

namespace ttower
{
	static TasksManager* tasksMng = nullptr;

	// Initialize function
	void initialize()
	{
		tasksMng = new TasksManager();
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
	
}