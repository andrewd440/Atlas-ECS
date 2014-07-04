#include "ComponentIdentifier.h"

namespace Atlas
{
	ComponentIdentifier::ComponentIdentifier()
		: mID(nextID++)
		, mBit(nextBit)
	{
		nextBit <<= 1;
	}


	unsigned int ComponentIdentifier::getID() const
	{
		return mID;
	}

	std::bitset<BITSIZE> ComponentIdentifier::getBit() const
	{
		return mBit;
	}

	unsigned int ComponentIdentifier::nextID = 0;
	std::bitset<BITSIZE> ComponentIdentifier::nextBit(1);
}