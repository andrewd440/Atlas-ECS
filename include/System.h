#pragma once
#include <memory>
#include <vector>
#include <bitset>

#include "Bitsize.h"
#include "Entity.h"
#include "ComponentIdentifierManager.h"

namespace Atlas
{
	/**
	* Base class for all Systems
	*/
	class System : public NonCopyable
	{
	public:
		/** Standard pointer when referring to a System */
		typedef std::unique_ptr<System> Ptr;

		/**
		* Creates a new System.
		* @param world - the World object that owns this System
		*/
		System(World& world);
		virtual												~System();

		/**
		* Proccesses all Entities relevant to this System.
		* @param dt - update time
		*/
		virtual void										update(float dt) = 0;

		/**
		* Checks to see if the System is interested in an Entity based on which
		* Components it owns. This is called everytime an Entity removes or adds
		* a Component. If the System is no longer interested in an Entity that
		* it already contains, the Entity will be removed from the System.
		* @param Entity - the Entity to be checked
		*/
		virtual void										checkInterest(Entity& Entity);

		/**
		* Retrieves the system type bits that are assigned to this System.
		* @return Bitset assigned to this System
		*/
		std::bitset<BITSIZE>								getSystemBits() const;

		/**
		* Prints Entities in the System, as well as this System's TypeBits and SystemBits
		*/
		void												toString();

	protected:
		template <typename T>
		/**
		* Adds a Component type for the System to process.
		*
		* Usage Example: (in HealthSystem constructor)
		* ~~~~~~~~~~~~~~~~~~~~~
		* addComponentType<HealthComponent>();
		* ~~~~~~~~~~~~~~~~~~~~~
		*/
		void												addComponentType()
		{
			mTypeBits |= ComponentIdentifierManager::getBits<T>();
		}

		/**
		* Retrieves the Component bit types that the System will process.
		* @return Bitset of Component types
		*/
		std::bitset<BITSIZE>								getTypeBits() const;

		/**
		* Retrieves the Entity::IDs of interested Entities
		* @return Container of Entity::IDs
		*/
		const std::vector<Entity::ID>&				getEntities() const;

		/**
		* Retrieves the World object for this System
		*/
		World&												getWorld() const;

	private:
		friend class SystemManager;  // Give full access to SystemManager

		/**
		* Removes an Entity from the System.
		* @params Entity - the Entity to be removed
		*/
		virtual void										remove(Entity& Entity);
		
		/**
		* Assigns a bitset for the System
		* @params Bit - the bit to be assigned
		*/
		void												setSystemBits(const std::bitset<BITSIZE>& Bit);

	private:
		World&												mWorld;
		std::vector<Entity::ID>								mEntities;
		std::bitset<BITSIZE>								mTypeBits;
		std::bitset<BITSIZE>								mSystemBits;
	};
}