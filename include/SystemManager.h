#pragma once
#include "System.h"

#include <vector>
#include <memory>

namespace Atlas
{
	class World;

	/**
	* A manager for all Systems that are used.
	*/
	class SystemManager : public NonCopyable
	{
	public:
		/**
		* Creates a new SystemManager.
		* @param world - the World object that owns this SystemManager
		*/
		SystemManager(World& world);

		/**
		* Adds a new System.
		* Usage Example:
		~~~~~~~~~~~~~~~~
		* Atlas::World world;
		* SystemManager.addSystem(Atlas::System::Ptr(new HealthSystem(world)));
		~~~~~~~~~~~~~~~~
		* @param system - the System to be added.
		*/
		void addSystem(System::Ptr system);
		
		template <typename T>
		/**
		* Retrieves a specified System.
		* Usage Example:
		~~~~~~~~~~~~
		* HealthSystem* system = SystemManager.getSystem<HealthSystem>();
		~~~~~~~~~~~~
		* @return pointer to the System.
		*/
		T* getSystem()
		{
			System* system = NULL;

			for (const auto& s : mSystems)
				if (typeid(*s) == typeid(T))
				{
					system = s.get();
					break;
				}

			// make sure the System is there and cast is safe
			assert(dynamic_cast<T*>(system));
			return static_cast<T*>(system);
		}

		/**
		* Updates all Systems.
		* Update order is based on the order that Systems are added to the SystemManager.
		* @param dt - update time
		*/
		void update(float dt);

		/**
		* Checks to see if the any Systems contained in the SystemManager is interested 
		* in an Entity based on which Components it owns.
		* @param entity - the Entity to be checked
		*/
		void checkInterest(Entity& entity);

		template <typename T>
		/**
		* Removes a System.
		* Usage Example:
		~~~~~~~~~~~~~~~~
		* systemManager.removeSystem<HealthSystem>();
		~~~~~~~~~~~~~~~~
		*/
		void removeSystem();

		/**
		* Prints the number of active Systems and the details of each of those Systems
		*/
		void toString();

	private:
		std::vector<System::Ptr>                            mSystems;
		World&                                              mWorld;
	};
}