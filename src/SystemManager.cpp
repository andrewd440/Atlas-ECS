#include "SystemManager.h"
#include "SystemBitManager.h"
#include "Utilities.h"

#include <cassert>
#include <iostream>

namespace Atlas
{
	SystemManager::SystemManager(World& world)
		: mWorld(world)
		, mSystems()
	{
	}

	void SystemManager::addSystem(System::Ptr system)
	{
		// Assign system bits
		system->setSystemBits(SystemBitManager::getBitsFor(system.get()));

		mSystems.push_back(std::move(system));
	}

	void SystemManager::update(float dt)
	{
		for (auto& system : mSystems)
				system->update(dt);
	}

	void SystemManager::checkInterest(Entity& e)
	{
		for (auto& system : mSystems)
			system->checkInterest(e);
	}

	template <typename Type>
	void SystemManager::removeSystem()
	{
		for (auto& system : mSystems)
			if (typeid(system) == Type)
				system = nullptr;
	}

	void SystemManager::toString()
	{
		using namespace std;

		cout << "-------------------------------------------------"
			<< "\n|\t\tSystemManager\t\t\t|"
			<< "\n-------------------------------------------------"
			<< endl;

		cout << "Active Systems: " << mSystems.size() << endl;

		for (const auto& system : mSystems)
			system->toString();

		cout << endl;

	}
}