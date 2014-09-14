#pragma once
#include <stack>
#include <vector>
#include <memory>
#include <cassert>

#include "Entity.h"
#include "ComponentIdentifier.h"

namespace Atlas
{
	class World;

	/**
	* Manages all Entities and Components within the a World.
	* Entities and Components will be directly or indirectly retrieved
	* and added through the EntityManager.
	*/
	class EntityManager : public NonCopyable
	{
	public:
		/**
		* Creates a new EntityManager.
		* @param world - the World object that owns this EntityManager
		*/
		explicit EntityManager(World& world);

		/**
		* Removes all entities that have been set to inactive
		*/
		void update();

		/**
		* Creates an empty Entity
		* @returns Reference to the new Entity
		*/
		Entity& createEntity();

		/**
		* Retreives an active Entity
		* @param ID - The Entity's ID
		* @returns Reference to the Entity
		*/
		Entity& getEntity(const Entity::ID& ID) const;

		/**
		* Attaches a Component to an Entity
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* entityManager.addComponent(entity, Atlas::Component::Ptr(new HealthComponent()));
		~~~~~~~~~~~~~~~~~~
		* @param entity - The Entity to add the Component to
		* @param component - Component to add
		*/
		void addComponent(Entity& entity, Component::Ptr component);

		/**
		* Removes a Component from an Entity
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* healthIdentifier = ComponentIdentifierManager::getType<HealthComponent>();
		* entityManager.removeComponent(entity, healthIdentifier);
		~~~~~~~~~~~~~~~~~~
		* @param entity - The Entity to remove a Component from
		* @param componentIdentifier - Identifier for the Component
		*/
		void removeComponent(Entity& entity, const ComponentIdentifier& componentIdentifier);

		template <typename T>
		/**
		* Retrieve a specific Component from an Entity
		* @param entity - The targeted Entity
		* @return Pointer to the derived type Component
		*/
		T* getComponentFor(const Entity& entity) const
		{
			return getComponentFor<T>(entity.getID());
		}

		template <typename T>
		/**
		* Retrieve a specific Component from an Entity
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* HealthComponent* health = entityManager.getComponentFor<HealthComponent>(ID);
		* health->hitpoints -= damage;
		~~~~~~~~~~~~~~~~~~
		* @param ID - The targeted Entity's ID
		* @return Pointer to the derived type Component
		*/
		T* getComponentFor(const Entity::ID& ID) const
		{
			// grab the component from the vector
			const auto& componentID = ComponentIdentifierManager::getID<T>();
			Component* component = mComponentsByType[componentID][ID].get();

			// make sure the compnonent is there and a cast is safe
			assert(component != nullptr);
			assert(dynamic_cast<T*>(component) != nullptr);

			return static_cast<T*>(component);
		}

		/**
		* Retrieves all the Components attached to an Entity.
		* @param entity - The targeted Entity
		* @return Vector of Component pointers from the Entity
		*/
		std::vector<Component*> getAllComponentsFor(const Entity& entity);

		/**
		* Removes and destroys all the Components attached to a Entity.
		* @param entity - The targeted Entity
		*/
		void removeAllComponentsFor(Entity& entity);

		/**
		* Prints the contents of all active Entities and displays the number of inactive Entities
		*/
		void toString();

	private:
		/**
		* Resets an Entity and moves it from the active Entity container to the dead Entity pool
		* @param entity - The targeted Entity
		*/
		void removeEntity(Entity& entity);

	private:
		unsigned int                mActiveEntityCount;
		Entity::ID                  mNextAvaibleID;
		World&                      mWorld;

		/** Holds all entities with the ID being used as an index */
		std::vector<Entity::Ptr>   mActiveEntities;

		/** Used as a pool for entity reuse */
		std::stack<Entity::Ptr>    mDeadEntities;

		/**
		* Holds all Components sorted by its parent Entity and type.
		* Rows are sorted by ComponentID
		* Columns are sorted by ID
		*/
		std::vector<std::vector<Component::Ptr>> mComponentsByType;

		/** Temp container used when retrieving components for a single Entity */
		std::vector<Component*>      mEntityComponents;
	};
}