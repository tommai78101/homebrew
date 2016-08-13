#pragma once

#ifndef PLAYER_HEADER
#	define PLAYER_HEADER

#include "../common.h"
#include "entity.h"

namespace Entity {
	class Player {
	public:
		//Trigger camera manipulation
		bool cameraManipulateFlag;
		
		bool inversePitchFlag;
		float rotationPitch, rotationYaw;
		float speed;
		s16 touchX, touchY, oldTouchX, oldTouchY, offsetTouchX, offsetTouchY;
		u16 counter;
		C3D_FVec cameraPosition;

		Player();
		void Update(u32 downKey, u32 heldKey, u32 upKey, touchPosition touchInput);
		void RenderUpdate(C3D_Mtx* viewMatrix);
	};
};

#endif
