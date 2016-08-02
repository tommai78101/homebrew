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
		TransformComponent
	};
	
	struct Component {
		ComponentType type;
		std::shared_ptr<GameObject> parent;
		
		Component();
		virtual ~Component();
		
		void SetParent(GameObject* parent);
		
		virtual void Update() = 0;
		virtual void RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix) = 0;
		virtual void Out() = 0;
	};

	class PhysicsComponent : public Component {
	public:
		float ax, ay, az, vx, vy, vz;
		const float GravityY = -0.4f;

		PhysicsComponent();
		PhysicsComponent(PhysicsComponent& copy);

		void Update() override;
		void RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix) override;
		void Out() override;
	};
	
	class TransformComponent : public Component {
	public:
		float scaleX, scaleY, scaleZ;
		float rotationPitch, rotationYaw, rotationRoll;
		
		TransformComponent();
		TransformComponent(TransformComponent& copy);
		
		void Update() override;
		void RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix) override;
		void Out() override;
	};
};

#endif
