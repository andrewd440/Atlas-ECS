#include "EntityManager.h"
#include "World.h"

#include <iostream>


namespace
{
	const int POOLSIZE = 100;
}

namespace Atlas
{
	EntityManager::EntityManager(World& world)
		: mWorld(world)
		, mActiveEntityCount(0)
		, mNextAvaibleID(0)
		, mActiveEntities(POOLSIZE)
		, mDeadEntities()
		, mComponentsByType(BITSIZE)
		, mEntityComponents()
	{
	}

	void EntityManager::update()
	{
		// remove inactive entities
		for (auto& entity : mActiveEntities)
			if (entity && !entity->isActive())
				removeEntity(*entity);
	}

	Entity& EntityManager::createEntity()
	{
		std::unique_ptr<Entity> e;

		// If a dead entity is pooled, set it to active and it will be the created entity
		if (!mDeadEntities.empty())
		{
			e = std::move(mDeadEntities.top());
			mDeadEntities.pop();
		}
		// if not, allocate a new entity, move it into our vector and increament ID
		else
		{
			e.reset(new Entity(mWorld, mNextAvaibleID++));
		}

		e->setActive(true);
		mActiveEntityCount++;

		Entity::ID id = e->getID();

		// make sure the id fits the container
		if (mActiveEntities.capacity() <= id)
		{
			mActiveEntities.resize(id * 2 + 1);
		}

		mActiveEntities[id] = std::move(e);

		return *mActiveEntities[id];

	}

	void EntityManager::removeEntity(Entity& entity)
	{
		// Only remove inactive entities
		assert(!entity.isActive());

		const auto& id = entity.getID();

		mWorld.getGroupManager().removeFromAllGroups(entity);

		// Deactivate entity and reset properties
		removeAllComponentsFor(entity);
		mActiveEntities[id]->reset();

		// Move entity to dead entity pool and set active element to null
		mDeadEntities.push(std::move(mActiveEntities[id]));

		mActiveEntities[id] = nullptr;

		mActiveEntityCount--;
	}

	Entity& EntityManager::getEntity(const Entity::ID& id) const
	{
		assert(id < mActiveEntities.size());
		return *mActiveEntities[id];
	}

	void EntityManager::addComponent(Entity& entity, Component::Ptr component)
	{
		const ComponentIdentifier& identifier = ComponentIdentifierManager::getType(typeid(*component));
		const Entity::ID& eID = entity.getID();

		auto& typeComponents = mComponentsByType[identifier.getID()];

		// make sure the id fits the container
		if (typeComponents.capacity() <= eID)
		{
			typeComponents.resize(eID * 2 + 1);
		}

		// check if entity already has component type
		if (typeComponents[eID] != nullptr)
		{
			removeComponent(entity, identifier);
		}

		entity.addComponentBit(identifier.getBit());
		typeComponents[eID] = std::move(component);

		// Check all systems for interest in new component
		mWorld.getSystemManager().checkInterest(entity);
	}

	void EntityManager::removeComponent(Entity& entity, const ComponentIdentifier& id)
	{
		// Check if specific component vector not out of range
		assert(mComponentsByType[id.getID()].capacity() > entity.getID());

		// Check if entity has component first
		assert(mComponentsByType[id.getID()][entity.getID()] != nullptr);

		entity.removeComponentBit(id.getBit());
		mComponentsByType[id.getID()][entity.getID()] = nullptr;

		// Check all systems to see if still interested in entity
		mWorld.getSystemManager().checkInterest(entity);
	}

	std::vector<Component*> EntityManager::getAllComponentsFor(const Entity& entity)
	{
		mEntityComponents.clear();

		const auto& entityBits = entity.getComponentBits();

		for (int i = 0; i < entityBits.size(); i++)
		{
			if (entityBits[i])
				mEntityComponents.push_back(mComponentsByType[i][entity.getID()].get());
		}

		return mEntityComponents;
	}

	void EntityManager::removeAllComponentsFor(Entity& entity)
	{
		const auto& id = entity.getID();

		for (int i = 0; i < mComponentsByType.size(); i++)
		{
			// check if vector is out of range and if there is a component for the entity present
			if (mComponentsByType[i].size() > id && mComponentsByType[i][id] != nullptr)
			{
				// get ComponentIdentifier for this component
				const auto& type = ComponentIdentifierManager::getType(typeid(*mComponentsByType[i][id]));

				entity.removeComponentBit(type.getBit());
				mComponentsByType[i][id] = nullptr;
			}
		}

		// Check all systems to remove entity from them
		mWorld.getSystemManager().checkInterest(entity);
	}

	void EntityManager::toString()
	{
		using namespace std;

		cout << "-------------------------------------------------"
			<< "\n|\t\tEntityManager\t\t\t|"
			<< "\n-------------------------------------------------"
			<< endl;

		cout << "\t\tActive Entities\t\t\t"
			<< "\n-------------------------------------------------"
			<< endl;

		for (const auto& entity : mActiveEntities)
			if (entity != nullptr)
				entity->toString();

		cout << "\t\tInactive Entities: " << mDeadEntities.size() << "\t\t"
			<< "\n-------------------------------------------------"
			<< endl << endl;
	}
}