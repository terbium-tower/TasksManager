/***********************************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include "../TManager.h"

namespace ttower
{
	// Initialize function
	void initialize();

	// Tasks Functions
	void update( float dt );
	
	void addTask( TaskCallback callback, TaskType type );
	void addTimedTask( TaskCallback callback, TaskType type, float seconds );

	
}