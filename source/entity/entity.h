#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

#include "../common.h"
#include "../engine/component.h"

namespace Entity {
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

		template<typename Derived> std::shared_ptr<Derived> AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			auto result = std::shared_ptr<Derived>(new Derived());
			this->components.push_back(result);
			return result;
		}
		
		template<typename Derived, typename... TArgs> std::shared_ptr<Derived> AddComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			auto result = std::shared_ptr<Derived>(new Derived(args...));
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
