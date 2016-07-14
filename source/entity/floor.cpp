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
		Mtx_Translate(modelMatrix, 0.0f, -5.0f, 0.0f);
		Mtx_Scale(modelMatrix, 100.0f, 0.001f, 100.0f);
	}
};
