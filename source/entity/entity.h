#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

#include "../common.h"

namespace Entity {
	enum class ComponentType {
		AbstractComponent,
		PhysicsComponent,
		ScaleComponent
	};
	
	struct Component {
		ComponentType type;
		
		Component();
		virtual ~Component();
		virtual void Update() = 0;
		virtual void RenderUpdate(C3D_Mtx* modelMatrix) = 0;
		virtual void Out() = 0;
	};

	class PhysicsComponent : public Component {
	public:
		float ax, ay, az, vx, vy, vz, px, py, pz;
		const float GravityY = -0.4f;

		PhysicsComponent();
		PhysicsComponent(PhysicsComponent& copy);

		void Update() override;
		void RenderUpdate(C3D_Mtx* modelMatrix) override;
		void Out() override;
	};
	
	class ScaleComponent : public Component {
	public:
		float scaleX, scaleY, scaleZ;
		
		ScaleComponent();
		ScaleComponent(ScaleComponent& copy);
		
		void Update() override;
		void RenderUpdate(C3D_Mtx* modelMatrix) override;
		void Out() override;
	};
	
	//--------------------------------------------------------------------------------------

	class GameObject {
	public:
		std::vector<std::shared_ptr<Component>> components;
		bool renderFlag, updateFlag;
		u32 vertexListSize, listElementSize;
		void* vertexBuffer;
		
		GameObject(const Vertex list[], int size);
		
		virtual ~GameObject();
		virtual void Update();
		virtual void Render();
		void Release();
		void RenderUpdate(C3D_Mtx* modelMatrix);
		void ConfigureBuffer();

		template<typename Derived> void AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			auto result = std::shared_ptr<Derived>(new Derived());
			this->components.push_back(std::move(result));
		}
		
		template<typename Derived, typename... TArgs> void AddComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			auto result = std::shared_ptr<Derived>(new Derived(args...));
			this->components.push_back(std::move(result));
		}
		
		template<typename Derived> std::shared_ptr<Derived> GetComponent() {
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			for (size_t i = 0; i < this->components.size(); i++){
				Derived* result = static_cast<Derived*>(this->components[i].get());
				if (result){
					return std::static_pointer_cast<Derived>(this->components[i]);	
				}
			}
			return nullptr;
		}
	};
};

#endif
