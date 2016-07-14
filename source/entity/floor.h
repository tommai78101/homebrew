#pragma once

#ifndef FLOOR_HEADER
#	define FLOOR_HEADER

#include "../utility/common.h"
#include "../engine/core.h"
#include "entity.h"

namespace Engine {
	class Floor : public Entity {
	private:
		
	public:
		Floor(const Vertex list[], const int listSize);
		Floor(const Floor& copy);
		~Floor();
		
		virtual void Update() override;
		virtual void RenderUpdate(C3D_Mtx* modelMatrix) override;
	};
};

#endif
