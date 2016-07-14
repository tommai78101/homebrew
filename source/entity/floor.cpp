#include "floor.h"

namespace Engine {
	Floor::Floor(const Vertex list[], const int listSize) : Entity(list, listSize) {
	}
	
	Floor::Floor(const Floor& copy) : Entity(copy) {
	}
	
	Floor::~Floor() {
		
	}
	
	void Floor::Update(){
	}
	
	void Floor::RenderUpdate(C3D_Mtx* modelMatrix) {
		Mtx_Scale(modelMatrix, 10.0f, 1.0f, 1.0f);
	}
};
