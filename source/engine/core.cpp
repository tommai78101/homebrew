#include "core.h"

namespace Engine {
	Core::Core(){
		text(4, 0, "Initializing core engine.");
	}
	
	Core::~Core(){
		text(4, 0, "Deinitializing core engine.");
	}
};
