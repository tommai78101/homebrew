#pragma once

#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "main.h"

int main(){
	gfxInitDefault();
	PrintConsole output;
	consoleSelect(consoleInit(GFX_BOTTOM, &output));

	Engine::Core& core = Engine::Core::Instance();
	core.Initialize();

	u32 down, held, up;
	touchPosition touchInput;

	while (aptMainLoop()){
		hidScanInput();
		down = hidKeysDown();
		held = hidKeysHeld();
		up = hidKeysUp();
		hidTouchRead(&touchInput);
		if (down & KEY_START){
			break;
		}

		core.Update(down, held, up, touchInput);
		core.Render();
	}

	core.Release();
	gfxExit();
	return 0;
}