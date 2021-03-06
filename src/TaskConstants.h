/********************** *************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>
#include <vector>
#include <list>
#include <memory>

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
}