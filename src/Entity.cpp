#include "Entity.h"
#include "EntityManager.h"
#include "Utilities.h"
#include "World.h"
#include "ComponentIdentifierManager.h"

#include <iostream>
namespace Atlas
{
	Entity::Entity(World& world, ID id)
		: mEntityManager(world.getEntityManager())
		, mID(id)
		, mIsActive(false)
		, mComponentBits()
		, mSystemBits()
	{
	}

	std::vector<Component*> Entity::getAllComponents() const
	{
		return mEntityManager.getAllComponentsFor(*this);
	}

	void Entity::addComponent(Component::Ptr component)
	{
		mEntityManager.addComponent(*this, std::move(component));
	}

	void Entity::setActive(bool flag)
	{
		mIsActive = flag;
	}

	bool Entity::isActive() const
	{
		return mIsActive;
	}

	void Entity::setID(ID id)
	{
		mID = id;
	}

	Entity::ID Entity::getID() const
	{
		return mID;
	}

	void Entity::reset()
	{
		mComponentBits = 0;
		mSystemBits = 0;
	}


	std::bitset<BITSIZE> Entity::getComponentBits() const
	{
		return mComponentBits;
	}

	void Entity::addComponentBit(const std::bitset<BITSIZE>& bit)
	{
		mComponentBits |= bit;
	}

	void Entity::removeComponentBit(const std::bitset<BITSIZE>& bit)
	{
		mComponentBits &= ~bit;
	}

	void Entity::setSystemBit(const std::bitset<BITSIZE>& bit)
	{
		mSystemBits |= bit;
	}

	void Entity::removeSystemBit(const std::bitset<BITSIZE>& bit)
	{
		mSystemBits &= ~bit;
	}

	std::bitset<BITSIZE> Entity::getSystemBits() const
	{
		return mSystemBits;
	}

	void Entity::toString() const
	{
		using namespace std;
		const auto& components = getAllComponents();

		cout << "ID: " << mID
			<< "\nComponentBits: " << mComponentBits.to_string()
			<< "\nComponents: ";

		for (const auto& c : components)
		{
			cout << typeidStringFormator(c) << ", ";
		}

		cout << "\nActive: " << mIsActive << endl << endl;
	}
}