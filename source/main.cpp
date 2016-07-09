#include "main.h"

int main() {
	gfxInitDefault();
	PrintConsole bottomScreen;
	consoleSelect(consoleInit(GFX_BOTTOM, &bottomScreen));
	
	text(0, 0, "This is the bottom screen.");
	text(1, 0, "Press START to exit.");
	
	Engine::Core core;
	
	while (aptMainLoop()){
		hidScanInput();
		if (hidKeysDown() & KEY_START){
			break;
		}
		
		gspWaitForVBlank();
	}
	
	gfxExit();
	return 0;
}
