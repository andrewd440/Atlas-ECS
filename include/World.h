#pragma once
#include "EntityManager.h"
#include "SystemManager.h"
#include "GroupManager.h"

#include <memory>

namespace Atlas
{
	/**
	* Represents the game world
	*/
	class World
	{
	public:
		/** 
		* Default constructor 
		*/
		World();

		/**
		* Updates the World.
		* @param dt - update time
		*/
		void													update(float dt);

		/**
		* Creates an empty Entity.
		* @return an empty Entity.
		*/
		Entity&													createEntity();

		/**
		* Retrieves an Entity.
		* @param id - the id for the Entity
		* @return an Entity
		*/
		Entity&													getEntity(Entity::ID id) const;

		/** Retrieves the EntityManager */
		EntityManager&											getEntityManager();

		/** Retrieves the SystemManager */
		SystemManager&											getSystemManager();

		/** Retrieves the GroupManager */
		GroupManager&											getGroupManager();

	private:
		EntityManager											mEntityManager;
		SystemManager											mSystemManager;
		GroupManager											mGroupManager;
	};
}