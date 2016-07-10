#pragma once

#ifndef ENGINE_HEADER
#	define ENGINE_HEADER

//Common utility header
#include "../utility/common.h"

//Application header
#include "../utility/output.h"
#include "../entity/entity.h"


//Engine namespace
//Will contain all engine related features.
namespace Engine {
	class Core {
	private:
		int uLoc_projection;
		int uLoc_modelView;
		float distZ;
		float angleX;
		float angleY;
		
		//void* vbo_data;
		
		std::vector<Entity> entityList;
		
		Output* output;
		
		C3D_Mtx projectionMatrix;
		C3D_LightEnv lightEnvironment;
		C3D_Light light;
		C3D_LightLut lut_Phong;
		C3D_RenderTarget* leftTarget;
		C3D_RenderTarget* rightTarget;
		
		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;
		
		void Initialize();
		void SceneInitialize();
		void SceneRender(float interOcularDistance);
		void SceneExit();
		
	public:
		Core(Output* output);
		~Core();
		void Update(u32 keyDown);
		void Render();
		Output* GetOutput() const;
	};
};

#endif
