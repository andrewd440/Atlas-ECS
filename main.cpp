#include <iostream>
#include "World.h"
#include "SystemManager.h"
#include "GroupManager.h"

struct DummyComponent : public Atlas::Component
{
	int number;
};

struct DummyComponent2 : public Atlas::Component
{

};

struct DummySystem : public Atlas::System
{
	DummySystem(Atlas::World& world) :System(world)
	{
		addComponentType<DummyComponent2>();
	};
	void update(float dt) {};

	int x;
};

struct DummySystem2 : public Atlas::System
{
	DummySystem2(Atlas::World& world) :System(world)
	{
		addComponentType<DummyComponent>();
	};
	void update(float dt) {};
};

int main()
{
	Atlas::World world;

	Atlas::EntityManager& manager = world.getEntityManager();
	Atlas::SystemManager& sManager = world.getSystemManager();
	auto& gManager = world.getGroupManager();

	sManager.addSystem(Atlas::System::Ptr(new DummySystem(world)));
	sManager.addSystem(Atlas::System::Ptr(new DummySystem2(world)));

	Atlas::Entity& e = manager.createEntity();
	Atlas::Entity& w = manager.createEntity();

	manager.addComponent(e, Atlas::Component::Ptr(new DummyComponent()));
	e.addComponent(Atlas::Component::Ptr(new DummyComponent2()));
	w.addComponent(Atlas::Component::Ptr(new DummyComponent2()));

	e.removeComponent<DummyComponent2>();

	gManager.addToGroup("Enemy", e);
	gManager.addToGroup("Enemy", w);

	gManager.addToGroup("JimmyJohn", e);

	e.setActive(false);

	auto dum = sManager.getSystem<DummySystem>();

	manager.toString();
	sManager.toString();

	world.update(2.f);

	manager.toString();
	sManager.toString();
	gManager.toString();

	return 0;
}