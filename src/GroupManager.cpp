#include "GroupManager.h"

#include <cassert>
#include <iostream>

namespace Atlas
{
	GroupManager::GroupManager()
		: mEntityGroups()
		, mGroupsByName()
	{

	}

	void GroupManager::addToGroup(const std::string& name, const Entity& entity)
	{
		const auto& ID = entity.getID();

		mGroupsByName[name].push_back(ID);

		// make sure vector is large enough
		if (mEntityGroups.size() <= ID)
			mEntityGroups.resize(ID * 2 + 1);

		mEntityGroups[ID].push_back(name);
	}

	std::vector<Entity::ID> GroupManager::getGroup(const std::string& name)
	{
		return mGroupsByName[name];
	}

	std::vector<std::string> GroupManager::getEntityGroups(const Entity& entity) const
	{
		const auto& ID = entity.getID();

		assert(mEntityGroups.size() > ID);
		return mEntityGroups[ID];
	}

	void GroupManager::removeFromGroup(const std::string& name, const Entity& entity, bool fullErase)
	{
		const auto& ID = entity.getID();

		auto positionItr = std::find(mGroupsByName[name].begin(), mGroupsByName[name].end(), ID);
		if (positionItr != mGroupsByName[name].end())
			mGroupsByName[name].erase(positionItr);

		// if the entity is not being removed from all groups, lookup and remove it from entityGroups
		if (!fullErase)
		{
			auto entityItr = std::find(mEntityGroups[ID].begin(), mEntityGroups[ID].end(), name);
			if (entityItr != mEntityGroups[ID].end())
				mEntityGroups[ID].erase(entityItr);
		}
	}

	void GroupManager::removeFromAllGroups(const Entity& entity)
	{
		const auto& ID = entity.getID();

		for (const auto& name : mEntityGroups[ID])
		{
			removeFromGroup(name, entity, true);
		}

		mEntityGroups[ID].clear();
	}

	void GroupManager::toString()
	{
		using namespace std;

		for (auto itr = mGroupsByName.begin(); itr != mGroupsByName.end(); itr++)
		{
			cout << itr->first << ": ";
			for (const auto& ID : itr->second)
				cout << ID << ", ";
			cout << endl;
		}
	}
}
