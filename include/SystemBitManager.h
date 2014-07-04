#pragma once
#include "NonCopyable.h"
#include "Bitsize.h"

#include <unordered_map>
#include <typeindex>

namespace Atlas
{
	/**
	* Used to distribute a unique bit identifier to each System created.
	*/
	class SystemBitManager : public NonCopyable
	{
	public:
		/**
		* Retrieves the bits for a System
		*
		* Usage Example:
		* ~~~~~~~~~~~~~~~~~~~~~~~
		* system.setSystemBits(Atlas::SystemBitManager::getBitsFor(typeid(HealthSystem)));
		* ~~~~~~~~~~~~~~~~~~~~~~~
		* @param type - the System of interest
		* @return A bitset containing the System bit
		*/
		static std::bitset<BITSIZE> getBitsFor(const std::type_index& type);

		template <typename T>
		/**
		* Retrieves the bits for a System
		*
		* Usage Example:
		* ~~~~~~~~~~~~~~~~~~~~~~~
		* system.setSystemBits(Atlas::SystemBitManager::getBitsFor<HealthSystem>());
		* ~~~~~~~~~~~~~~~~~~~~~~~
		* @param type - pointer to a System
		* @return A bitset containing the System bit
		*/
		static std::bitset<BITSIZE> getBitsFor(const T* type)
		{
			return getBitsFor(typeid(*type));
		}


	private:
		SystemBitManager() = default; 		//Not meant for instantiation

		static std::unordered_map<std::type_index, std::bitset<BITSIZE>>    mSystemBitMap;
		static std::bitset<BITSIZE>                                         mNextBit;
	};
}