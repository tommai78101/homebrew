#include "entity.h"

namespace Engine {
	Entity::Entity(const Vertex list[], int size) {
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
		
		//Other remaining stuffs.
		this->angleX = 0.0f;
		this->angleXSpeed = 0.0f;
		this->posX = 0.0f;
	}
	
	Entity::~Entity(){
		linearFree(this->vertexBuffer);
	}
	
	void Entity::Update(){
		//This is for game logic updates, for each individual entities in the engine.
		if (this->updateFlag){
			//Do stuff here....
			this->angleX += this->angleXSpeed * radian;
		}
	}
	
	void Entity::RenderUpdate(C3D_Mtx* modelMatrix) {
		//This update function will update entity properties.
		Mtx_Translate(modelMatrix, this->posX, 0.0f, 0.0f);
		Mtx_Translate(modelMatrix, 0.0, 0.0, -2.0 + sinf(this->angleX));
		Mtx_RotateX(modelMatrix, this->angleX, true);
		Mtx_RotateY(modelMatrix, this->angleX, true);
	}
	
	void Entity::Render(){
		if (this->renderFlag){
			//Since the entity object uses up the full vertex buffer, we start from the
			//beginning of the vertex buffer, and go through to the end of it.
			C3D_DrawArrays(GPU_TRIANGLES, 0, this->listElementSize);
		}
	}
	
	void Entity::ConfigureBuffer(){
		//Initialize and configure buffers.
		//The Buffer Info needs to be reset every time a new buffer is to take its place.
		//In other words, BufInfo_Init() is frequently used.
		C3D_BufInfo* bufferInfo = C3D_GetBufInfo();                  
		BufInfo_Init(bufferInfo);                                    
		BufInfo_Add(bufferInfo, this->vertexBuffer, sizeof(Vertex), 3, 0x210); 
	}
	
	u32 Entity::GetListSize() const {
		return this->listElementSize;
	}
	
	u32 Entity::GetTotalSize() const {
		return this->vertexListSize;
	}
	
	void* Entity::GetVertexBuffer() const {
		return this->vertexBuffer;
	}
	
	void Entity::SetUpdateFlag(bool value){
		this->updateFlag = value;
	}
	
	void Entity::SetRenderFlag(bool value){
		this->renderFlag = value;
	}
	
	void Entity::SetAngleXSpeed(float value) {
		this->angleXSpeed = value;
	}
	
	void Entity::SetPositionX(float value) {
		this->posX = value;
	}
	
	bool Entity::IsRenderEnabled() const {
		return this->renderFlag;
	}
	
	bool Entity::IsUpdateEnabled() const {
		return this->updateFlag;
	}
};
