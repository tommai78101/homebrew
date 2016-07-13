#pragma once

#ifndef FLOOR_HEADER
#	define FLOOR_HEADER

#include "../utility/common.h"
#include "entity.h"

namespace Engine {
	class Floor : public Entity {
	private:
		
	public:
		Floor(const Vertex list[], const int listSize);
		Floor(const Floor& copy);
		~Floor();
		
		void Update() override;
		void RenderUpdate(C3D_Mtx* modelMatrix) override;
	};
};

#endif
