#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<bitset>
#include<array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {

public:
	Entity* entity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {};
};

class Entity {
	
public:
	bool active = false;
	std::vector<Component*> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;


	void update() {
		for (auto& c : components) {
			c->update();
		}		
	}

	void draw() {
		for (auto& c : components) {
			c->draw();
		}
	};
	bool isActive() {
		return active;
	}

	void destroy() {
		active = false;
	}

	template <typename T> bool hasComponent() const {
		//return std::get<getComponentTypeID<T>()>(componentBitSet);
		return componentBitSet[getComponentTypeID<T>()]; 
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		Component* uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {

private:
	std::vector<std::unique_ptr<Entity>> entities;

	std::vector<std::vector<Component*>> componentArray;


public:


	void init() {

		
			
			for (auto& c : entities[0]->components) {

			std::vector<Component*> comp;
				componentArray.push_back(comp);
			}

		
		for (auto& e : entities) {

			int i = 0;

			for (auto& c : e->components) {

				componentArray[i].push_back(c);
				i++;
			}

			//e->update();
		}
	}


	void update() {
		for (auto& a : componentArray) {
			for (auto& c : a)
			 c->update();
		}
	}

	void draw() {
		for (auto& a : componentArray) {
			for (auto& c : a)
				c->draw();
		}
	}

	void resfresh() {
		//removes non active entities
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{

			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	
	std::vector<std::unique_ptr<Entity>>& getEntities()
	{
		return entities;
	}


	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};