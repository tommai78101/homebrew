#include "entity.h"

namespace Entity {
	Component::Component() {
		this->type = ComponentType::AbstractComponent;
	}
	
	Component::~Component(){ }

	//------------------------------------------------------------------------------------

	PhysicsComponent::PhysicsComponent() {
		this->type = ComponentType::PhysicsComponent;
		ax = ay = az = vx = vy = vz = px = py = pz = 0.0f;
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
		this->px = copy.px;
		this->py = copy.py;
		this->pz = copy.pz;
	}

	void PhysicsComponent::Update(){
		if (this->py < -5.0f) {
			this->ay *= -0.5f;
			this->vy *= -0.5f;
			if (std::abs(this->ay) < 0.02f){
				this->ay = 0.0f;
			}
		}
		else if (this->ay > this->GravityY){
			this->ay += this->GravityY / 30.0f;
		}

		this->vx += this->ax;
		this->vy += this->ay;
		this->vz += this->az;
		this->px += this->vx;
		this->py += this->vy;
		this->pz += this->vz;

		this->vx *= 0.2f;
		this->vy *= 0.2f;
		this->vz *= 0.2f;
	}

	void PhysicsComponent::RenderUpdate(C3D_Mtx* modelMatrix){
		Mtx_Translate(modelMatrix, this->px, this->py, this->pz);
	}

	void PhysicsComponent::Out(){
		std::cout << std::setprecision(3) << az << "    " << vz << "    " << pz << std::endl;
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
	
	//------------------------------------------------------------------------------------

	GameObject::GameObject(const Vertex list[], int size){
		//Setting array element size.
		this->listElementSize = size;

		//Setting list size.
		this->vertexListSize = size * sizeof(Vertex);

		//Initializing vertex list.
		//Create vertex buffer objects.
		this->vertexBuffer = linearAlloc(this->vertexListSize);
		std::memcpy(this->vertexBuffer, list, this->vertexListSize);

		//Enabling rendering flag.
		this->renderFlag = true;
		//Enabling updating flag.
		this->updateFlag = true;

		//Entity-Component stuffs.
		this->components.clear();
	}
	
	GameObject::~GameObject(){ }

	void GameObject::Update(){
		for (size_t i = 0; i < this->components.size(); i++){
			this->components[i]->Update();
			//this->components[i]->Out();
		}
	}

	void GameObject::Render(){
		if (this->renderFlag) {
			//Since the entity object uses up the full vertex buffer, we start from the
			//beginning of the vertex buffer, and go through to the end of it.
			C3D_DrawArrays(GPU_TRIANGLES, 0, this->listElementSize);
		}
	}

	void GameObject::Release(){
		//Freeing the allocated memory.
		if (this->vertexBuffer){
			std::cout << "Freeing allocated memory." << std::endl;
			linearFree(this->vertexBuffer);
		}
	}

	void GameObject::RenderUpdate(C3D_Mtx* modelMatrix){
		//This update function will update entity properties.
		for (size_t i = 0; i < this->components.size(); i++) {
			this->components[i]->RenderUpdate(modelMatrix);
		}
	}

	void GameObject::ConfigureBuffer(){
		//Initialize and configure buffers.
		//The Buffer Info needs to be reset every time a new buffer is to take its place.
		//In other words, BufInfo_Init() is frequently used.
		C3D_BufInfo* bufferInfo = C3D_GetBufInfo();
		BufInfo_Init(bufferInfo);
		BufInfo_Add(bufferInfo, this->vertexBuffer, sizeof(Vertex), 3, 0x210);
	}
}
