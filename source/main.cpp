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
	int count = 0;
	
	output.Print("Entering render loop.");
	while (aptMainLoop()){
		hidScanInput();
		u32 downEvent = hidKeysDown();
		u32 heldEvent = hidKeysHeld();
		if ((downEvent & KEY_START) || (heldEvent & KEY_START)){
			break;
		}
		else if ((downEvent & KEY_A) || (heldEvent & KEY_A)){
			count++;
			std::stringstream s;
			s << "Hello world. Count: " << count;
			output.Print(s.str());
		}
		else if (downEvent & KEY_B){;
			output.SetReverseFlag(!output.GetReverseFlag());
			std::stringstream s;
			s << "Reversing output direction to " << (output.GetReverseFlag() == 1 ? "TRUE" : "FALSE") << ".";
			output.Print(s.str());
			output.PrintAll();
		}
		
		core.Update(downEvent);
		core.Render();
	}
	
	gfxExit();
	return 0;
}

