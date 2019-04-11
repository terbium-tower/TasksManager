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
	
	void addTask( TaskCallback callback );
	void addTimedTask( TaskCallback callback, ThreadType type, float seconds );

	
}