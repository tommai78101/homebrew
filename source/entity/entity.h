#pragma once

#ifndef ENTITY_HEADER
#	define ENTITY_HEADER

//Common header
#include "../utility/common.h"

namespace Engine {
	class Entity {
	protected:
		bool isEnabled;
		void* vertexList;
		u32 vertexListSize;
		u32 listElementSize;
		
	public:
		Entity(const Vertex list[], int size);
		~Entity();
		
		//Actions
		void Initialize(C3D_BufInfo* bufferInfo, u64 permutation);
		void Update();
		u32 Render(u32 start);
		
		//Setter
		void SetEnabled(bool value);
		
		//Getter
		u32 GetListSize() const;
		u32 GetTotalSize() const;
		
		//Conditionals
		bool IsEnabled() const;
	};
};


#endif
