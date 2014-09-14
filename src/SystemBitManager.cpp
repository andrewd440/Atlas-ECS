#include "SystemBitManager.h"

namespace Atlas
{
	std::bitset<BITSIZE> SystemBitManager::getBitsFor(const std::type_index& type)
	{
		// if the System is not in the map, assign a bit to it and add it to the map
		if (mSystemBitMap.find(type) == mSystemBitMap.end())
		{
			mSystemBitMap[type] = mNextBit;
			mNextBit <<= 1;
		}

		return mSystemBitMap[type];
	}

	std::bitset<BITSIZE> SystemBitManager::mNextBit(1);
	std::unordered_map<std::type_index, std::bitset<BITSIZE>> SystemBitManager::mSystemBitMap;
}