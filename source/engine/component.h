#pragma once

#ifndef COMPONENT_HEADER
#	define COMPONENT_HEADER

#include "../common.h"
#include "../entity/entity.h"

namespace Entity {
	class GameObject;
	
	enum class ComponentType {
		AbstractComponent,
		PhysicsComponent,
		ScaleComponent
	};
	
	struct Component {
		ComponentType type;
		std::shared_ptr<GameObject> parent;
		
		Component();
		virtual ~Component();
		
		void SetParent(GameObject* parent);
		
		virtual void Update() = 0;
		virtual void RenderUpdate(C3D_Mtx* modelMatrix) = 0;
		virtual void Out() = 0;
	};

	class PhysicsComponent : public Component {
	public:
		float ax, ay, az, vx, vy, vz;
		//float px, py, pz;
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
};

#endif
