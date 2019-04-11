/********************** *************
Terbium Tower | Author: Eugene Fomin
***********************************/
#pragma once

// Includes
#include <functional>

namespace ttower
{
	// Constants
	const int kInitializeTasksReserve = 100;

	// Aliases 
	using TaskCallback = std::function< void() >;

	// Enums
	enum class ThreadType : short
	{
		MainThread = 0,
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
		TimedTask( std::uint64_t _id = 0ull,
				   TaskCallback _callback = NULL,
				   float _seconds = 0.0f )
			: id( _id )
			, callback( _callback )
			, seconds( _seconds )
		{}

		std::uint64_t id;
		TaskCallback callback;
		float seconds;
	};
	
	// Functions
	inline void TasksManagerLog( const std::string& str )
	{
		printf( "%s", str.c_str() );
	}
}