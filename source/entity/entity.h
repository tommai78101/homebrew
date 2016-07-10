#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

//Common header
#include "../utility/common.h"

//Application headers
#include "../engine/core.h"

namespace Engine {
	class Entity {
	private:
		Core* core;
		void* vertexList;
		
	public:
		Entity(Core* core, std::vector<Vertex>* list);
		~Entity();
		void Initialize(C3D_BufInfo* bufferInfo, u64 permutation);
	};
};


#endif
