#include "entity.h"

namespace Engine {
	Entity::Entity(Vertex list[]){
		this->vertexList = linearAlloc(sizeof(list));
		std::memcpy(this->vertexList, list, sizeof(list));
	}
	
	Entity::~Entity(){
		linearFree(this->vertexList);
	}
	
	void Entity::Initialize(C3D_BufInfo* bufferInfo, u64 permutation){
		BufInfo_Add(bufferInfo, this->vertexList, sizeof(Vertex), 3, permutation);
	}
};
