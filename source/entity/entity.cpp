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
		this->isPickedUp = false;

		//Entity-Component stuffs.
		this->components.clear();
	}
	
	GameObject::~GameObject(){ }

	void GameObject::Update(){
		for (size_t i = 0; i < this->components.size(); i++){
			this->components[i]->Update();
			
			//Ignore this for now.
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

	void GameObject::RenderUpdate(C3D_FVec cameraPosition, C3D_Mtx& viewMatrix, C3D_Mtx* modelMatrix){
		//3D object pick-up.
		if (this->isPickedUp){
			//If true, allow the player to manipulate the object in the world.
			
			//Orient the object to face the camera when the object is picked up and held in the hands.
			this->rotation = Quat_MyLookAt(this->position, cameraPosition);
			
			//Creating an inverse matrix.
			C3D_Mtx inverse;
			Mtx_Copy(&inverse, &viewMatrix);                                           
			Mtx_Inverse(&inverse);                
			
			//Doing the simplified calculations.
			Mtx_Translate(modelMatrix, 0.0f, 0.0f, -3.0f, true);
			Mtx_Multiply(modelMatrix, &inverse, modelMatrix);
			
			//Decomposing the model matrix and obtaining the new object positions. See (Matrix Decomposition) for more info.
			this->position = FVec4_New(modelMatrix->r[0].w, modelMatrix->r[1].w, modelMatrix->r[2].w, 1.0f);
		}
		else {
			//If false, keep its new position and rotation in the world and go from there.
			Mtx_Translate(modelMatrix, this->position.x, this->position.y, this->position.z, true);
			C3D_Mtx rotationMatrix;
			Mtx_FromQuat(&rotationMatrix, this->rotation);
			
			//We multiply the model matrix with the rotation matrix, so model matrix will have the new rotation/orientation set.
			Mtx_Multiply(modelMatrix, modelMatrix, &rotationMatrix);
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
