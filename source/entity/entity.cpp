#include "entity.h"

namespace Entity {
	Component::~Component(){ }

	//------------------------------------------------------------------------------------

	PhysicsComponent::PhysicsComponent() {
		ax = ay = az = vx = vy = vz = px = py = pz = 0.0f;
		std::cout << "PhysicsComponent has been created." << std::endl;
	}

	void PhysicsComponent::Update(){
		if (this->az > this->GravityY){
			this->az += this->GravityY / 30.0f;
		}

		if (this->pz < -10.0f) {
			this->az *= -1.0f;
			this->vz *= -1.0f;
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

	void GameObject::Update(){
		for (size_t i = 0; i < this->components.size(); i++){
			this->components[i]->Update();
			this->components[i]->Out();
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
		linearFree(this->vertexBuffer);
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