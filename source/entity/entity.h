#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

#include "../common.h"
#include "../engine/component.h"

namespace Entity {
	class Component;
	
	class GameObject {
	public:
		bool renderFlag, updateFlag;
		void* vertexBuffer;
		C3D_FVec position;
		C3D_FVec scale;
		//float positionX, positionY, positionZ;
		C3D_FQuat rotation;
		u32 vertexListSize, listElementSize;
		std::vector<std::shared_ptr<Component>> components;
		
		GameObject(const Vertex list[], int size);
		
		virtual ~GameObject();
		virtual void Update();
		virtual void Render();
		void Release();
		void RenderUpdate(bool cameraManipulateFlag, C3D_FVec cameraPosition, C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix);
		void ConfigureBuffer();
		
		//Templates must go inside header files. This is the recommended method in C++.

		template<typename Derived> std::shared_ptr<Derived> AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived());
			result->SetParent(this);
			result->Initialize();
			this->components.push_back(result);
			return result;
		}
		
		template<typename Derived, typename... TArgs> std::shared_ptr<Derived> AddComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived(args...));
			result->SetParent(this);
			result->Initialize();
			this->components.push_back(result);
			return result;
		}
		
		//Returns shared pointer to a subclass of Component if found. Returns nullptr if not.
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
