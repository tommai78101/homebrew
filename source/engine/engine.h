#pragma once

#ifndef ENGINE_HEADER
#	define ENGINE_HEADER

#include "../common.h"
#include "../entity/entity.h"
#include "../entity/player.h"

//Shader headers
#include "vshader_shbin.h"

using namespace Entity;

namespace Engine {
	class Core {
	private:
		int uLoc_projection;
		int uLoc_model;
		int uLoc_view;

		C3D_Mtx projectionMatrix;
		C3D_Mtx viewMatrix;
		C3D_LightEnv lightEnvironment;
		C3D_Light light;
		C3D_LightLut lut_Phong;
		C3D_RenderTarget* leftTarget;
		C3D_RenderTarget* rightTarget;

		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;

		Player player;


	public:
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		static Core& Instance();
		~Core();
		void Initialize();
		void LoadObjects();
		void Update(u32 down, u32 held, u32 up, touchPosition touch);
		void Render();
		void Release();
		void SceneRender(float interOcularDistance);
		void SceneExit();
	};
};

#endif
