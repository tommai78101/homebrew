#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

//Common header
#include "../utility/common.h"

namespace Engine {
	class Entity {
	private:
		Vertex* vertexList;
		
	public:
		Entity(Vertex list[]);
		~Entity();
		void Initialize(C3D_BufInfo* bufferInfo, u64 permutation);
	};
};


#endif
