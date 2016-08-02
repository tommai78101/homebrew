#include "component.h"

namespace Entity {
	Component::Component() {
		this->type = ComponentType::AbstractComponent;
	}
	
	Component::~Component(){ }
	
	void Component::SetParent(GameObject* parent){
		this->parent = std::shared_ptr<GameObject>(parent);
	}

	//------------------------------------------------------------------------------------

	PhysicsComponent::PhysicsComponent() {
		this->type = ComponentType::PhysicsComponent;
		ax = ay = az = vx = vy = vz = 0.0f;
		std::cout << "PhysicsComponent has been created." << std::endl;
	}
	
	PhysicsComponent::PhysicsComponent(PhysicsComponent& copy) {
		this->type = copy.type;
		this->ax = copy.ax;
		this->ay = copy.ay;
		this->az = copy.az;
		this->vx = copy.vx;
		this->vy = copy.vy;
		this->vz = copy.vz;
	}

	void PhysicsComponent::Update(){
		if (this->parent->positionY < 0.0f) {
			this->ay *= -0.8f;
			this->vy *= -0.8f;
			if (std::abs(this->ay) < std::numeric_limits<float>::epsilon()){
				this->ay = 0.0f;
			}
		}
		else if (this->ay > this->GravityY){
			this->ay += this->GravityY / 30.0f;
		}

		this->vx += this->ax;
		this->vy += this->ay;
		this->vz += this->az;
		this->parent->positionX += this->vx;
		this->parent->positionY += this->vy;
		this->parent->positionZ += this->vz;

		this->vx *= 0.2f;
		this->vy *= 0.2f;
		this->vz *= 0.2f;
	}

	void PhysicsComponent::RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix){
		Mtx_Translate(modelMatrix, this->parent->positionX, this->parent->positionY, this->parent->positionZ);
	}

	void PhysicsComponent::Out(){
		std::cout << std::setprecision(3) << az << "    " << vz << "     " << this->parent->positionZ << std::endl;
	}

	//------------------------------------------------------------------------------------
	
	TransformComponent::TransformComponent() {
		this->type = ComponentType::TransformComponent;
		this->scaleX = this->scaleY = this->scaleZ = 1.0f;
		this->rotationPitch = this->rotationYaw = this->rotationRoll = 0.0f;
	}
	
	TransformComponent::TransformComponent(TransformComponent& copy){
		this->type = copy.type;
		this->scaleX = copy.scaleX;
		this->scaleY = copy.scaleY;
		this->scaleZ = copy.scaleZ;
		this->rotationPitch = copy.rotationPitch;
		this->rotationRoll = copy.rotationRoll;
		this->rotationYaw = copy.rotationYaw;
	}
	
	void TransformComponent::Update(){ }
	
	void TransformComponent::RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix){
		Mtx_RotateX(modelMatrix, this->rotationPitch, true);
		Mtx_RotateY(modelMatrix, this->rotationYaw, true);
		Mtx_RotateZ(modelMatrix, this->rotationRoll, true);
		//Mtx_Scale(modelMatrix, this->scaleX, this->scaleY, this->scaleZ);
	}
	
	void TransformComponent::Out() { }
}
