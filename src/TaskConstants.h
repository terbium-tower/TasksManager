/***********************************
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
	enum class TaskType : short
	{
		MainThread = 0,
		NewThread
	};

	// Structs
	struct Task
	{
		TaskType type;
		TaskCallback callback;
	};
}