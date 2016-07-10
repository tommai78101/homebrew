#include "main.h"

int main() {
	gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, true);
	
	PrintConsole bottomScreen;
	consoleSelect(consoleInit(GFX_BOTTOM, &bottomScreen));
	
	Output output;
	output.print("Press A to send dummy messages.");
	output.print("Press B to reverse output logs.");
	output.print("Press START to quit.");
	output.print(" ");
	
	
	Engine::Core core(&output);
	int count = 0;
	
	output.print("Entering render loop.");
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
			output.print(s.str());
		}
		else if (downEvent & KEY_B){;
			output.setReverseFlag(!output.getReverseFlag());
			std::stringstream s;
			s << "Reversing output direction to " << (output.getReverseFlag() == 1 ? "TRUE" : "FALSE") << ".";
			output.print(s.str());
			output.printAll();
		}
		
		core.Update(downEvent);
		core.Render();
		
		//gspWaitForVBlank();
	}
	
	gfxExit();
	return 0;
}
