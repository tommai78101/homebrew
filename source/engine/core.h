#pragma once

#ifndef ENGINE_HEADER
#	define ENGINE_HEADER

//Common utility header
#include "../utility/common.h"

//Application header
#include "../utility/output.h"
#include "../entity/entity.h"
#include "../entity/floor.h"


//Engine namespace
//Will contain all engine related features.
namespace Engine {
	class Core {
	private:
		int uLoc_projection;
		int uLoc_model;
		int uLoc_view;
		float camX;
		float camZ;
		float rotationX;
		float rotationY;
		float playerSpeed;
		
		std::vector<Entity*> entityList;
		
		Output* output;
		
		C3D_Mtx projectionMatrix;
		C3D_Mtx viewMatrix;
		C3D_LightEnv lightEnvironment;
		C3D_Light light;
		C3D_LightLut lut_Phong;
		C3D_RenderTarget* leftTarget;
		C3D_RenderTarget* rightTarget;
		
		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;
		
		//Singleton.
		//Constructor/Destructor.
		Core(Output* output);
		~Core();
		
		//Discarding methods we don't want. (C++03)
		Core(Core const&);
		void operator=(Core const&);
		
		//Action functions.
		void Initialize();
		void SceneInitialize();
		void SceneRender(float interOcularDistance);
		void SceneExit();
		
	public:
		//Singleton.
		static Core& GetInstance();
		
		//Important Action functions.
		void LoadEntities();
		void Update(u32 keyDown, u32 keyHeld, u32 keyUp);
		void Render();
		
		//Helper methods
		void AddEntity(Entity* entity);
		
		//Getter/Setters.
		Output* GetOutput() const;
	};
};

#endif
