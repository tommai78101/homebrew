#pragma once

#ifndef ENGINE_HEADER
#	define ENGINE_HEADER

//Common utility header
#include "../utility/common.h"

//Application header
#include "../utility/output.h"

namespace Engine {
	class Core {
	private:
		Output* output;
		
	public:
		Core(Output* output);
		~Core();
		void Update(u32 keyDown);
	};
};

#endif
