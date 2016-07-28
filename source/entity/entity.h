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
		
		//Polymorphic cloning pattern with smart pointers.
		virtual std::unique_ptr<Component> Clone() const = 0;
		
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
		
		//Polymorphic cloning pattern with smart pointers.
		virtual std::unique_ptr<Component> Clone() const override;
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
		std::vector<std::unique_ptr<Component>> components;
		
		
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
		
		//Entity-Component System Component Creatora (they all go in the headers, per C++ standards)
		template<typename T>
		T& CreateComponent(){
			static_assert(std::is_base_of<Component, T>::value, "Derived class is not subclass of Component class.");
			auto result = std::unique_ptr<T>(new T());
			this->components.push_back(std::move(result));
			return *result;
		}
		
		template<typename T, typename... TArgs>
		T& CreateComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, T>::value, "Derived class is not subclass of Component class.");
			auto result = std::unique_ptr<T>(new T(std::forward(args...)));
			this->components.push_back(std::move(result));
			return *result;
		}
		
		//Taken from:
		//http://stackoverflow.com/a/27104183/1016891
		template<class T>
		std::unique_ptr<T> copy_unique(const std::unique_ptr<T>& source){
			return source ? std::make_unique<T>(*source) : nullptr;
		}
		
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
