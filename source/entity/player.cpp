#include "player.h"

namespace Entity {
	Player::Player(){
		this->camX = 0.0f;
		this->camZ = 10.0f;		//Points  towards the positive Z axis. This also means default yaw orientation is positive Z.
		this->rotationPitch = degToRad(0.0f); 
		this->rotationYaw = degToRad(0.0f);
		this->speed = 0.04f;
		
		//Other variables
		this->offsetTouchX = this->offsetTouchY = 0.0f;
		this->oldTouchX = this->oldTouchY = 0;
		this->touchX = 0; 
		this->touchY = 0;
		this->counter = 0;
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
				this->oldTouchX = touchInput.py;
				this->oldTouchY = touchInput.px;
			}
			else if (keyHeld & KEY_TOUCH) {
				this->offsetTouchY = this->oldTouchY - touchInput.px;
				this->offsetTouchX = this->oldTouchX - touchInput.py;

				//Inverted Pitch (X axis) 
				//There exists this method of calculating overall rotation for rotation X, Y, in 1 line of code:
				float f = std::fmod(((((float) (this->offsetTouchX + this->touchX) * sensitivity / 65536.0f) * 180.0f) - 90.0f), 360.0f);
				this->rotationPitch = -degToRad(f);
				
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

				//Applying same rotation, so as to get a smoother transition from Hold to Release button events.
				//This is optional, by the way.
				//std::fmod = Floating Point Modulus. Fetches the remainder, equivalent to integer modulus.
				float f = std::fmod(((((float) this->touchX * sensitivity / 65536.0f) * 180.0f) - 90.0f), 360.0f);
				this->rotationPitch = -degToRad(f);
				
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
		
		if (this->counter > 50){
			text(10, 0, "                                     ");
			text(11, 0, "                                     ");
			text(10, 0, "Touch Coordinates: " + ToString(this->touchX) + "  " + ToString(this->touchY));
			text(11, 0, "Yaw: " + ToString(this->rotationYaw) + "   Pitch: " + ToString(this->rotationPitch));
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