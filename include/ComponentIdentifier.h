#pragma once
#include "Bitsize.h"

#include <memory>

namespace Atlas
{
	/**
	* Handle used for Components.
	* Distributes a unique ID and Bitset for Components.
	* ComponentIdentifierManager uses this class to assign
	* Identifiers for each Component.
	*/
	class ComponentIdentifier
	{
	public:
		/** Standard pointer used for ComponentIdentifier */
		typedef std::unique_ptr<ComponentIdentifier> Ptr;

		/**
		* Retrieves the unique ID for the identifier
		*/ 
		unsigned int						getID() const;

		/**
		* Retrieves the unique bitset for the identifier
		*/ 
		std::bitset<BITSIZE>				getBit() const;

	private:
		friend class ComponentIdentifierManager; 		// Give full access to the Manager

		ComponentIdentifier(); 		// Only to be created by the manager

	private:
		static unsigned int					nextID;
		static std::bitset<BITSIZE>			nextBit;

		unsigned int						mID;
		std::bitset<BITSIZE>				mBit;
	};
}