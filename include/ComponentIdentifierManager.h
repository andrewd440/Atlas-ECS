#pragma once
#include "Bitsize.h"

#include <unordered_map>
#include <typeindex>
#include <memory>

namespace Atlas
{
	class ComponentIdentifier;

	/**
	* Used to assign a unique ID and Bit to a System when
	* added to the SystemManager.
	*/
	class ComponentIdentifierManager
	{
	public:

		/**
		* Retrieves an identifier for a Component.
		* If an identifier has not been assigned to the Component, one is created and assigned.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* ComponentIdentifierManager::getType(typeid(HealthComponent))
		~~~~~~~~~~~~~~~~~~
		* @param index - type_index for the Component
		*/
		static ComponentIdentifier& getType(const std::type_index& index);

		template <typename T>
		/**
		* Retrieves an identifier for a Component.
		* If an identifier has not been assigned to the Component, one is created and assigned.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* ComponentIdentifierManager::getType<HealthComponent>()
		~~~~~~~~~~~~~~~~~~
		*/
		static ComponentIdentifier& getType()
		{
			return getType(typeid(T));
		}

		template <typename T>
		/**
		* Retrieves the Bit assigned to a Component.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* ComponentIdentifierManager::getBits<HealthComponent>()
		~~~~~~~~~~~~~~~~~~
		*/
		static std::bitset<BITSIZE> getBits()
		{
			return getType(typeid(T)).getBit();
		}

		template <typename T>
		/**
		* Retrieves the ID assigned to a Component.
		*
		* Usage Example:
		~~~~~~~~~~~~~~~~~~
		* ComponentIdentifierManager::getID<HealthComponent>()
		~~~~~~~~~~~~~~~~~~
		*/
		static unsigned int getID()
		{
			return getType(typeid(T)).getID();
		}

	private:
		ComponentIdentifierManager() = default;	// Not meant for instantiation

		static std::unordered_map < std::type_index,
			std::unique_ptr < ComponentIdentifier >> ComponentMap;	// Map of Components-to-ComponentIdentifiers
	};
}