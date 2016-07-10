#include "core.h"

namespace Engine {
	Core::Core(Output* out){
		this->output = out;
		this->output->print("Initializing core.");
	}
	
	Core::~Core(){
		this->output->print("Deinitializing core.");
	}
	
	void Core::Update(u32 keyDown){
		
	}
};
