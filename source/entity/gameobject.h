#pragma once

#ifndef GAMEOBJECT_HEADER
#	define GAMEOBJECT_HEADER

//Common header file
#include "../utility/common.h"

//C++11 specific codes.
namespace Engine {
	//Components
	struct Component {
		virtual ~Component(); 
		virtual void Start();
		virtual void Update();
	};
	
	struct PhysicsComponent : public Component {
		const float GravityZ = -0.4f;
		
		float accelX;
		float accelY;
		float accelZ;
		float velocityX;
		float velocityY;
		float velocityZ;
		float positionX;
		float positionY;
		float positionZ;
		
		PhysicsComponent();
		void Start() override;
		void Update() override;
	};
	
	//Entity-Component System
	class GameObject {
	public:
		//Vector list of components to be added.
		std::vector<std::unique_ptr<Component>> components;
		
		template<typename T, typename... TArgs> T& CreateComponent(TArgs && ... args);
		template<typename T> T& CreateComponent();
		
		void Start();
		void Update();
	};
};
#endif
