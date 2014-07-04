#include "World.h"

namespace Atlas
{
	World::World() 
	: mEntityManager(*this)
	, mSystemManager(*this)
	, mGroupManager()
	{
	}

	void World::update(float dt)
	{
		mEntityManager.update();
		mSystemManager.update(dt);
	}

	Entity& World::createEntity()
	{
		return mEntityManager.createEntity();
	}

	Entity& World::getEntity(Entity::ID id) const
	{
		return mEntityManager.getEntity(id);
	}

	EntityManager& World::getEntityManager()
	{
		return mEntityManager;
	}

	SystemManager& World::getSystemManager()
	{
		return mSystemManager;
	}

	GroupManager& World::getGroupManager()
	{
		return mGroupManager;
	}
}