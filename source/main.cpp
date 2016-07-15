#include "main.h"

int main() {
	gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, true);
	
	PrintConsole bottomScreen;
	consoleSelect(consoleInit(GFX_BOTTOM, &bottomScreen));
	
	Engine::Core& core = Engine::Core::GetInstance();
	Output* output = core.GetOutput();
	output->Print(" ");
	output->Print(" ");
	output->Print("Citro3D Tutorial Demo");
	output->Print("Written by wedr");
	output->Print(" ");
	output->Print("Special thanks to:");
	output->Print("#3dsdev, #3dshacks, fincs, smealum");
	output->Print("/r/gamedev, /r/3dshacks, Reddit");
	output->Print(" ");
	output->Print("Controls:");
	output->Print(" ");
	output->Print("* Use touchscreen for FPS camera view.");
	output->Print("* L+C-Stick for console camera view.");
	output->Print("* Hold A to run/move faster.");
	output->Print("* Press B to reverse output logs.");
	output->Print("* Press START to quit.");
	output->Print(" ");
	
	//For use with obtaining touch input position.
	touchPosition touchInput;
	u32 downEvent, heldEvent, upEvent;
	
	while (aptMainLoop()){
		hidScanInput();
		hidTouchRead(&touchInput);
		downEvent = hidKeysDown();
		heldEvent = hidKeysHeld();
		upEvent = hidKeysUp();
		
		if ((downEvent & KEY_START) || (heldEvent & KEY_START)){
			break;
		}
		
		core.Update(downEvent, heldEvent, upEvent, touchInput);
		core.Render();
	}
	
	gfxExit();
	return 0;
}


