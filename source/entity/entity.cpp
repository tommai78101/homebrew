#include "entity.h"

namespace Engine {
	Entity::Entity(Core* core, std::vector<Vertex>* list) {
		//Initializing class members.
		this->core = core;
		
		//Initializing vertex list.
		this->vertexList = linearAlloc(list->size());
		std::memcpy(this->vertexList, list->data(), list->size());
	}
	
	Entity::~Entity(){
		linearFree(this->vertexList);
	}
	
	void Entity::Initialize(C3D_BufInfo* bufferInfo, u64 permutation){
		BufInfo_Add(bufferInfo, this->vertexList, sizeof(Vertex), 3, permutation);
	}
};
