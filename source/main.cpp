#include "main.h"

int main() {
	gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, true);
	
	PrintConsole bottomScreen;
	consoleSelect(consoleInit(GFX_BOTTOM, &bottomScreen));
	
	Output output;
	output.Print("Press A to send dummy messages.");
	output.Print("Press B to reverse output logs.");
	output.Print("Press START to quit.");
	output.Print(" ");
	
	Engine::Core core(&output);
	
	output.Print("Entering render loop.");
	while (aptMainLoop()){
		hidScanInput();
		u32 downEvent = hidKeysDown();
		u32 heldEvent = hidKeysHeld();
		u32 upEvent = hidKeysHeld();
		
		if ((downEvent & KEY_START) || (heldEvent & KEY_START)){
			break;
		}
		
		core.Update(downEvent, heldEvent, upEvent);
		core.Render();
	}
	
	gfxExit();
	return 0;
}


