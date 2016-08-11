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
		float camX, camZ;
		float rotationPitch, rotationYaw;
		float speed;
		s16 touchX, touchY, oldTouchX, oldTouchY, offsetTouchX, offsetTouchY;
		u16 counter;
		
		//Keep old view matrix.
		C3D_Mtx oldViewMatrix;

		Player();
		void Update(u32 downKey, u32 heldKey, u32 upKey, touchPosition touchInput);
		void RenderUpdate(C3D_Mtx* viewMatrix);
		void Manipulate(std::shared_ptr<GameObject> obj, C3D_Mtx& currentProjectionMatrix, C3D_Mtx& currentViewMatrix, C3D_Mtx& modelMatrix);
	};
};

#endif
