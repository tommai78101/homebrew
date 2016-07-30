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
		//px = py = pz = 0.0f;
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
		//this->px = copy.px;
		//this->py = copy.py;
		//this->pz = copy.pz;
	}

	void PhysicsComponent::Update(){
		//if (this->py < -5.0f) {
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
		//this->px += this->vx;
		//this->py += this->vy;
		//this->pz += this->vz;
		this->parent->positionX += this->vx;
		this->parent->positionY += this->vy;
		this->parent->positionZ += this->vz;

		this->vx *= 0.2f;
		this->vy *= 0.2f;
		this->vz *= 0.2f;
	}

	void PhysicsComponent::RenderUpdate(C3D_Mtx* modelMatrix){
		//Mtx_Translate(modelMatrix, this->px, this->py, this->pz);
		Mtx_Translate(modelMatrix, this->parent->positionX, this->parent->positionY, this->parent->positionZ);
	}

	void PhysicsComponent::Out(){
		//std::cout << std::setprecision(3) << az << "    " << vz << "    " << pz << std::endl;
		std::cout << std::setprecision(3) << az << "    " << vz << "     " << this->parent->positionZ << std::endl;
	}

	//------------------------------------------------------------------------------------
	
	ScaleComponent::ScaleComponent() {
		this->type = ComponentType::ScaleComponent;
		this->scaleX = this->scaleY = this->scaleZ = 1.0f;
	}
	
	ScaleComponent::ScaleComponent(ScaleComponent& copy){
		this->type = copy.type;
		this->scaleX = copy.scaleX;
		this->scaleY = copy.scaleY;
		this->scaleZ = copy.scaleZ;
	}
	
	void ScaleComponent::Update(){ }
	
	void ScaleComponent::RenderUpdate(C3D_Mtx* modelMatrix){
		Mtx_Scale(modelMatrix, this->scaleX, this->scaleY, this->scaleZ);
	}
	
	void ScaleComponent::Out() { }
}
