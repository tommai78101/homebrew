#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

//Common header
#include "../utility/common.h"

namespace Engine {
	class Entity; 
	
	//-----------------------------  Components  ----------------------------------------
	
	struct Component {
		Entity* parent;
		
		virtual ~Component();
		virtual void Update() = 0;
		virtual void RenderUpdate(C3D_Mtx* modelMatrix) = 0;
		
		void SetParent(Entity& parent);
		Entity* GetParent() const;
	};
	
	class PhysicsComponent : public Component {
	protected:
		float accelerationX, accelerationY, accelerationZ;
		float velocityX, velocityY, velocityZ;
		float positionX, positionY, positionZ;
		const float GravityZ = 0.4f;
		
	public:
		PhysicsComponent();
		void Update() override;
		void RenderUpdate(C3D_Mtx* modelMatrix) override;
	};
	
	//-------------------------------  Entity  ------------------------------------------	
	
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
		
		//Public Entity-Component System components list.
		std::vector<Component*> components;
		
		
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
		
		//Creators
		template<typename T> T& CreateComponent();
		template<typename T, typename... TArgs> T& CreateComponent(TArgs&&... args);
		
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
