#include "entity.h"

namespace Entity {
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
		
		//Remaining class member initialization.
		this->position.x = this->position.y = this->position.z = 0.0f;
		this->scale.x = this->scale.y = this->scale.z = 0.0f;
		this->rotation = Quat_Identity();

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

	void GameObject::RenderUpdate(C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix){
		//Convert quaternion to model matrix;
		Mtx_FromQuat(modelMatrix, this->rotation);
		
		//This update function will update entity properties.
		for (size_t i = 0; i < this->components.size(); i++) {
			this->components[i]->RenderUpdate(viewMatrix, modelMatrix);
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
