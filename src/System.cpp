#include "System.h"
#include "Utilities.h"
#include <iostream>

namespace Atlas
{
	System::System(World& world)
		: mWorld(world)
		, mTypeBits()
		, mSystemBits()
		, mEntities()
	{
		////////////////////////////////////////////////////////////////////////////
		////// Call addComponentType() in derived classes //////////////////////////
		////////////////////////////////////////////////////////////////////////////
	}

	void System::checkInterest(Entity& e)
	{
		// check if entity is already in our system and if this system is
		// interested in processing it
		bool contains = (e.getSystemBits() & mSystemBits) == mSystemBits;
		bool interest = (e.getComponentBits() & mTypeBits) == mTypeBits;

		// It is not in the system, but we are interested
		if (!contains && interest && mTypeBits.any())
		{
			mEntities.push_back(e.getID());
			e.setSystemBit(mSystemBits);
		}
		// It is in the system, but we are not interested
		else if (contains && !interest && mTypeBits.any())
		{
			remove(e);
		}
	}

	void System::remove(Entity& e)
	{
		e.removeSystemBit(mSystemBits);
		mEntities.erase(std::find(mEntities.begin(), mEntities.end(), e.getID()));
	}

	void System::setSystemBits(const std::bitset<BITSIZE>& bit)
	{
		mSystemBits = bit;
	}

	std::bitset<BITSIZE> System::getSystemBits() const
	{
		return mSystemBits;
	}

	std::bitset<BITSIZE> System::getTypeBits() const
	{
		return mTypeBits;
	}

	const std::vector<Entity::ID>& System::getEntities() const
	{
		return mEntities;
	}

	World& System::getWorld() const
	{
		return mWorld;
	}

	void System::toString()
	{
		using namespace std;

		cout << "-------------------------------------------------"
			<< "\n|\t\t" << typeidStringFormator(this) << "\t\t\t|"
			<< "\n-------------------------------------------------"
			<< endl;

		cout << "Interested Entities: ";
		for (const auto& e : mEntities)
			cout << e << ", ";

		cout << "\nSystemBits: " << mSystemBits
			<< "\nComponentBits: " << mTypeBits << endl << endl;



	}

	System::~System()
	{
	}
}