#include "main.h"

int main() {
	gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, true);
	
	PrintConsole bottomScreen;
	consoleSelect(consoleInit(GFX_BOTTOM, &bottomScreen));
	
	Engine::Core& core = Engine::Core::GetInstance();
	Output* output = core.GetOutput();
	output->Print("Press A to send dummy messages.");
	output->Print("Press B to reverse output logs.");
	output->Print("Press START to quit.");
	output->Print(" ");
	
	output->Print("Entering render loop.");
	while (aptMainLoop()){
		hidScanInput();
		u32 downEvent = hidKeysDown();
		u32 heldEvent = hidKeysHeld();
		u32 upEvent = hidKeysUp();
		
		if ((downEvent & KEY_START) || (heldEvent & KEY_START)){
			break;
		}
		
		core.Update(downEvent, heldEvent, upEvent);
		core.Render();
	}
	
	gfxExit();
	return 0;
}


