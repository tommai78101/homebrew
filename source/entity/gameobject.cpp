#include "gameobject.h"

namespace Engine {
	//Component base class.
	Component::~Component(){
		
	}
	
	void Component::Start(){
		
	}
	
	void Component::Update(){
		
	}
	
	//----------------------------------------------------------------
	
	//Physics Component derived class.
	PhysicsComponent::PhysicsComponent(){
		this->accelX = this->accelY = this->accelZ = 0.0f;
		this->velocityX = this->velocityY = this->velocityZ = 0.0f;
		this->positionX = this->positionY = this->positionZ = 0.0f;
	}
	
	void PhysicsComponent::Start() {
		this->accelX = this->accelY = this->accelZ = 0.0f;
		this->velocityX = this->velocityY = this->velocityZ = 0.0f;
		this->positionX = this->positionY = this->positionZ = 0.0f;
	}
	
	void PhysicsComponent::Update(){
		//X
		this->velocityX += this->accelX;
		this->positionX += this->velocityX;
		//Y
		this->velocityY += this->accelY;
		this->positionY += this->velocityY;
		//Z
		this->velocityZ += this->accelZ;
		this->positionZ += this->velocityZ;
	}
	
	//----------------------------------------------------------------
	
	//GameObject base object class.
	template<typename T, typename... TArgs> 
	T& GameObject::CreateComponent(TArgs&&... args){
		auto result = std::unique_ptr<T>(new T(std::forward<TArgs...>(args...)));
		static_assert(std::is_base_of<Component, T>::value, "Requires a subclass of the Component class, with constructor and arguments.");
		this->components.push_back(std::move(result));
		return *result;
	}
	
	template<typename T>
	T& GameObject::CreateComponent() {
		auto result = std::unique_ptr<T>(new T());
		static_assert(std::is_base_of<Component, T>::value, "Requires a subclass of the Component class.");
		this->components.push_back(std::move(result));
		return *result;
	}
	
	void GameObject::Start(){
		for (size_t i = 0; i < this->components.size(); i++){
			this->components[i]->Start();
		}
	}
	
	void GameObject::Update(){
		for (size_t i = 0; i < this->components.size(); i++){
			this->components[i]->Update();
		}
	}
	
	
	
};
