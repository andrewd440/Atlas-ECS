#pragma once
#include "Component.h"
#include "NonCopyable.h"
#include "Bitsize.h"
#include "ComponentIdentifierManager.h"

#include <vector>
#include <memory>

namespace Atlas
{
	class World;

	/**
	* Used to represent any game object.
	* Acts as a grouping/container for Components.
	*/
	class Entity : public NonCopyable
	{
	public:
		/** ID type for an Entity */
		typedef unsigned int ID; 

		/** Standard pointer used an Entity */
		typedef std::unique_ptr<Entity> Ptr; 

		template <typename Type>
		/**
		* Retrieves a specified Component from the Entity.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* HealthComponent* health = entity.getComponent<HealthComponent>();
		* health->hitpoints -= damage;
		~~~~~~~~~~~~~~~~~~
		* @return Component casted to it's derived type
		*/
		Type* getComponent() const
		{
			return mEntityManager.getComponentFor<Type>(*this);
		}

		/**
		* Retrieves all Components that are attached to the Entity.
		* @return All Components owned by the Entity
		*/
		std::vector<Component*>						getAllComponents() const;

		/**
		* Adds a Component to the Entity.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* entity.addComponent(Atlas::Component::Ptr(new HealthComponent()));
		~~~~~~~~~~~~~~~~~~
		* @param Component - component to be added
		*/
		void										addComponent(Component::Ptr Component);

		template <typename Type>
		/**
		* Removes a specified Component from the Entity.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* entity.removeComponent<HealthComponent>();
		~~~~~~~~~~~~~~~~~~
		*/
		void removeComponent()
		{
			mEntityManager.removeComponent(*this, ComponentIdentifierManager::getType<Type>());
		}

		/**
		* Retrieves the ID assigned to the Entity
		* @return The ID
		*/
		ID											getID() const;
		
		/**
		* Checks if the Entity is active
		* @return True if Entity is active
		*/
		bool										isActive() const;

		/**
		* Sets the active state of the Entity. Any inactive Entities will be
		* removed by the EntityManager.
		* @param Flag - status of Entity
		*/
		void										setActive(bool Flag);

		/**
		* Retrieves the Component bits in use by the Entity
		* @return Set of Component bits
		*/
		std::bitset<BITSIZE>						getComponentBits() const;

		/**
		* Sets a System bit to be assigned to the Entity
		* @param Bit - System bit to be added
		*/
		void										setSystemBit(const std::bitset<BITSIZE>& Bit);

		/**
		* Removes a System bit from the Entity
		* @param Bit - bit to be removed
		*/
		void										removeSystemBit(const std::bitset<BITSIZE>& Bit);

		/**
		* Retrieves the System bits assigned to the Entity
		* @return Set of System bits
		*/
		std::bitset<BITSIZE>						getSystemBits() const;

		/**
		* Prints the ID, Component bits, Component list, and Active state of the Entity.
		*/
		void										toString() const;

	private:
		friend class EntityManager;

		Entity(World& world, ID id);	// Only the EntityManager creates Entities

		/**
		* Sets the ID for the Entity.
		* A unique ID is assigned to the Entity when created by the EntityManager.
		* @param ID - id to be assigned
		*/
		void										setID(ID ID);

		/**
		* Resets Component and System properties held by the Entity object
		*/
		void										reset();

		/**
		* Adds a Component bit to the Entity.
		* Used by the EntityManager when a Component is added to an Entity.
		* @param Bit - bit to be added
		*/
		void										addComponentBit(const std::bitset<BITSIZE>& Bit);
		
		/**
		* Removes a Component bit from the Entity.
		* Used by the EntityManager when a Component is removed from an Entity.
		* @param Bit - bit to be removed
		*/
		void										removeComponentBit(const std::bitset<BITSIZE>& Bit);

	private:
		ID											mID;
		std::bitset<BITSIZE>						mComponentBits;
		std::bitset<BITSIZE>						mSystemBits;
		EntityManager&								mEntityManager;
		bool										mIsActive;
	};
}