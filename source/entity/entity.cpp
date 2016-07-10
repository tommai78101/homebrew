#include "entity.h"

namespace Engine {
	Entity::Entity(const Vertex list[], int size) {
		//Setting array element size.
		this->listElementSize = size;
		
		//Setting list size.
		this->vertexListSize = size * sizeof(Vertex);
		
		//Initializing vertex list.
		this->vertexList = linearAlloc(this->vertexListSize);
		std::memcpy(this->vertexList, list, this->vertexListSize);
		
		//Enabling rendering flag.
		this->isEnabled = true;
	}
	
	Entity::~Entity(){
		linearFree(this->vertexList);
	}
	
	void Entity::Initialize(C3D_BufInfo* bufferInfo, u64 permutation){
		BufInfo_Add(bufferInfo, this->vertexList, sizeof(Vertex), 3, permutation);
	}
	
	u32 Entity::GetListSize() const {
		return this->listElementSize;
	}
	
	u32 Entity::GetTotalSize() const {
		return this->vertexListSize;
	}
	
	void Entity::SetEnabled(bool value){
		this->isEnabled = value;
	}
	
	bool Entity::IsEnabled() const {
		return this->isEnabled;
	}
	
	void Entity::Update() {
		//This update function will update entity properties.
	}
	
	u32 Entity::Render(u32 start){
		//start: This parameter is the starting index of a splice of BufInfo. This entity will be rendered by
		//providing the aforementioned splice to the C3D_DrawArrays().
		//No matter what happens, we return the starting index + offset of the finished-rendering splice back. 
		//This offset is the size of array elements of the vertex array.
		if (this->isEnabled){
			C3D_DrawArrays(GPU_TRIANGLES, start, this->listElementSize);
		}
		return start + this->listElementSize;
	}
};
