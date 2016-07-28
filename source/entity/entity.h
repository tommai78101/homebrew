#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

#include "../common.h"

namespace Entity {
	struct Component {
		virtual ~Component();
		virtual void Update() = 0;
		virtual void RenderUpdate(C3D_Mtx* modelView) = 0;
		virtual void Out() = 0;
	};

	class PhysicsComponent : public Component {
	public:
		float ax, ay, az, vx, vy, vz, px, py, pz;
		const float GravityY = -0.4f;

		PhysicsComponent();

		void Update() override;
		void RenderUpdate(C3D_Mtx* modelView) override;
		void Out() override;
	};

	class GameObject {
	public:
		std::vector<std::unique_ptr<Component>> components;
		bool renderFlag, updateFlag;
		u32 vertexListSize, listElementSize;
		void* vertexBuffer;
		
		GameObject(const Vertex list[], int size);

		virtual void Update();
		virtual void Render();
		void Release();
		void RenderUpdate(C3D_Mtx* modelMatrix);
		void ConfigureBuffer();

		template<typename Derived> Derived& AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			auto result = std::unique_ptr<Derived>(new Derived());
			this->components.push_back(std::move(result));
			std::cout << "Subclass of Component has been added." << std::endl;
			return *result;
		}
	};
};

#endif