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
		float angleX;
		float angleXOffset;
		float posX;
		float posY;
		
	public:
		//RAII requirements.
		Entity(const Vertex list[], int size);
		Entity(const Entity& copy);
		~Entity();
		
		//Actions
		void Update();
		void RenderUpdate(C3D_Mtx* modelMatrix);
		void Render();
		void ConfigureBuffer();
		
		//Setter
		void SetRenderFlag(bool value);
		void SetUpdateFlag(bool value);
		void SetAngleXSpeed(float value);
		void SetAngleXOffset(float value);
		void SetPositionX(float value);
		void SetPositionY(float value);
		
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
