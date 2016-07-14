#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

//Common header
#include "../utility/common.h"

namespace Engine {
	class Entity {
	protected:
		bool updateFlag;
		bool renderFlag;
		void* vertexBuffer;
		u32 vertexListSize;
		u32 listElementSize;
		
		float angleXSpeed;
		float angleXOffset;
		
	public:
		//Public variables (to avoid writing a lot of setters/getters)
		float posX;
		float posY;
		float posZ;
		float rotX;
		float rotY;
		float rotZ;
		float scaleX;
		float scaleY;
		float scaleZ;
		
		
		//RAII requirements.
		Entity(const Vertex list[], int size);
		Entity(const Entity& copy);
		virtual ~Entity();
		
		//Virtual methods
		virtual void Update();
		virtual void RenderUpdate(C3D_Mtx* modelMatrix);
		
		//Methods
		void Render();
		void ConfigureBuffer();
		
		//Setter
		void SetRenderFlag(bool value);
		void SetUpdateFlag(bool value);
		void SetAngleXSpeed(float value);
		void SetAngleXOffset(float value);
		
//		void SetPositionX(float value);
//		void SetPositionY(float value);
//		void SetPositionZ(float value);
//		void SetRotationX(float value);
//		void SetRotationY(float value);
//		void SetRotationZ(float value);
//		void SetScaleX(float value);
//		void SetScaleY(float value);
//		void SetScaleZ(float value);
		
		//Getter
		void* GetVertexBuffer() const;
		u32 GetListSize() const;
		u32 GetTotalSize() const;
		
		//Conditionals
		bool IsRenderEnabled() const;
		bool IsUpdateEnabled() const;
	};
};


#endif
