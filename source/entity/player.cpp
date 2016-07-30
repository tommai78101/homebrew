#include "player.h"

namespace Entity {
	Player::Player(){
		this->camX = 0.0f;
		this->camZ = 10.0f;		//Points  towards the positive Z axis. This also means default yaw orientation is positive Z.
		this->rotationPitch = degToRad(-90.0f); 
		this->rotationYaw = degToRad(1.0f);
		this->speed = 0.04f;
		
		//Other variables
		this->offsetTouchX = this->offsetTouchY = 0.0f;
		this->oldTouchX = BOTTOM_SCREEN_WIDTH / 2;
		this->oldTouchY = BOTTOM_SCREEN_HEIGHT / 2;
		this->touchX = this->oldTouchX; 
		this->touchY = this->oldTouchY;
		this->counter = 0;
		this->inversePitchFlag = true;
	}

	void Player::Update(u32 keyDown, u32 keyHeld, u32 keyUp, touchPosition touchInput){
		//Game Controls

		//FPS Camera Facing.
		if (keyHeld & KEY_L) {
			if (keyHeld & KEY_LEFT) {
				this->rotationYaw -= radian;
				if (this->rotationYaw < degToRad(-180.0f)) {
					this->rotationYaw = degToRad(180.0f);
				}
			}
			else if (keyHeld & KEY_RIGHT) {
				this->rotationYaw += radian;
				if (this->rotationYaw > degToRad(180.0f)) {
					this->rotationYaw = degToRad(-180.0f);
				}
			}
			else if (keyHeld & KEY_UP) {
				this->rotationPitch += radian;
				if (this->rotationPitch > degToRad(89.9f)) {
					this->rotationPitch = degToRad(89.9f);
				}
			}
			else if (keyHeld & KEY_DOWN) {
				this->rotationPitch -= radian;
				if (this->rotationPitch < degToRad(-89.9f)) {
					this->rotationPitch = degToRad(-89.9f);
				}
			}
		}
		else {
			//FPS Camera Forward Movement.
			//Forward uses the cosine and sine calculations for traversing on the 
			//Cartesian coordinates, X, and Z axes.
			//Note strafing reverses the ordering of cosine and sine calculations, because
			//The cosine and sine calculations are rotated by 90 degrees counterclockwise.
			if (keyHeld & KEY_UP) {
				this->camX += std::sin(this->rotationYaw) * this->speed;
				this->camZ -= std::cos(this->rotationYaw) * this->speed;
			}
			else if (keyHeld & KEY_DOWN) {
				this->camX -= std::sin(this->rotationYaw) * this->speed;
				this->camZ += std::cos(this->rotationYaw) * this->speed;
			}
			else if (keyHeld & KEY_LEFT) {
				this->camX -= std::cos(this->rotationYaw) * this->speed;
				this->camZ -= std::sin(this->rotationYaw) * this->speed;
			}
			else if (keyHeld & KEY_RIGHT) {
				this->camX += std::cos(this->rotationYaw) * this->speed;
				this->camZ += std::sin(this->rotationYaw) * this->speed;
			}

			//Touchscreen cursor sensitivity. May need tweaking.
			//Akin to mouse sensitivity in FPS games.
			float sensitivity = 256.0f;

			//Touchscreen cursor offset positioning (aka. dragging)
			//We flipped the X and Y around, because we're using this for rotation, not position.
			//X = Pitch or rotation on the X axis.
			//Y = Yaw or rotation on the Y axis.
			//When releasing touch input, the value will default back to 0. Therefore, we need to check on
			//KEY_TOUCH to detect touchscreen press/hold/release events.
			if (keyDown & KEY_TOUCH) {
				this->oldTouchX = (s16) touchInput.py;
				this->oldTouchY = (s16) touchInput.px;
			}
			else if (keyHeld & KEY_TOUCH) {
				this->offsetTouchY = this->oldTouchY - (s16) touchInput.px;
				this->offsetTouchX = this->oldTouchX - (s16) touchInput.py;

				//Inverted Pitch (X axis) (multiply it by -1.0f)
				//There exists this method of calculating overall rotation for rotation X, Y, in 1 line of code:
				//float f = std::fmod(((((float) (this->offsetTouchX + this->touchX) * sensitivity / 65536.0f) * 180.0f)), 180.0f) - 90.0f;
				//float f = (std::max<float>(0.1f, std::min<float>((((float) (this->offsetTouchX + this->touchX)) * sensitivity / 65536.0f) * 180.0f, 179.9f))) - 90.0f;
				float f = (((float) (this->offsetTouchX + this->touchX)) / 65536.0f) * sensitivity * 180.0f;
				f = std::max<float>(-89.9f, std::min<float>(f, 89.9f));
				this->rotationPitch = degToRad(f);
				
				text(8, 0, "                   ");
				text(8, 0, "Pitch: " + ToString(f));
				
				
				f = std::fmod(((((float) (this->offsetTouchY + this->touchY) * sensitivity / 65536.0f) * 360.0f) - 180.0f), 360.0f) - 180.0f;
				this->rotationYaw = degToRad(f);

				text(9, 0, "                   ");
				text(9, 0, "Yaw: " + ToString(f));
			}
			else if (keyUp & KEY_TOUCH) {
				//Adding offset to the main touch coordinates.
				this->touchX += this->offsetTouchX;
				this->touchY += this->offsetTouchY;

				//Applying same rotation, so as to get a smoother transition from Hold to Release button events. (Includes pitch inversion)
				//This is optional, by the way.
				//std::fmod = Floating Point Modulus. Fetches the remainder, equivalent to integer modulus.
				//float f = std::fmod(((((float) this->touchX * sensitivity / 65536.0f) * 180.0f)), 180.0f) - 90.0f;
				//float f = (std::max<float>(0.1f, std::min<float>((((float) (this->offsetTouchX + this->touchX)) * sensitivity / 65536.0f) * 180.0f, 179.9f))) - 90.0f;
				float f = (((float) (this->touchX)) / 65536.0f) * sensitivity * 180.0f;
				f = std::max<float>(-89.9f, std::min<float>(f, 89.9f));
				this->rotationPitch = degToRad(f);
				this->touchX = std::max<float>(-127, std::min<float>(this->touchX, 127)); //Magic number. This resets the pitch offset value to the min/max dragging value.
				
				text(8, 0, "                   ");
				text(8, 0, "Pitch: " + ToString(f));
				
				f = std::fmod(((((float) this->touchY * sensitivity / 65536.0f) * 360.0f) - 180.0f), 360.0f) - 180.0f;
				this->rotationYaw = degToRad(f);
				
				text(9, 0, "                   ");
				text(9, 0, "Yaw: " + ToString(f));
			}
		}

		//Running Button.
		if ((keyDown & KEY_A) || (keyHeld & KEY_A)) {
			this->speed = 0.5f;
		}
		else if (keyUp & KEY_A) {
			this->speed = 0.05f;
		}
		
		//Inverse Pitch
		if (keyDown & KEY_X){
			this->inversePitchFlag = !this->inversePitchFlag;
		}
		
		if (this->counter > 50){
			text(10, 0, "                                     ");
			text(11, 0, "                                     ");
			text(12, 0, "                                     ");
			text(10, 0, "Touch Coordinates: " + ToString(this->touchX) + "  " + ToString(this->touchY));
			text(11, 0, "Old Touches: " + ToString(this->oldTouchX) + "  " + ToString(this->oldTouchY));
			text(12, 0, "Yaw: " + ToString(this->rotationYaw) + "   Pitch: " + ToString(this->rotationPitch));
			this->counter = 0;
		}
		else {
			this->counter++;
		}
	}

	void Player::RenderUpdate(C3D_Mtx* viewMatrix){
		Mtx_Identity(viewMatrix);
		Mtx_RotateX(viewMatrix, this->rotationPitch, true);			
		Mtx_RotateY(viewMatrix, this->rotationYaw, true);
		Mtx_Translate(viewMatrix, -this->camX, 0.0f, -this->camZ);
	}
};
