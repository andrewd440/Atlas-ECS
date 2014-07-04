#pragma once
#include "Entity.h"

#include <unordered_map>


namespace Atlas
{
	/**
	* Used to organize entities into named groups.
	*/
	class GroupManager : public NonCopyable
	{
	public:
																					/** Default Constructor */
																					GroupManager();

		/**
		* Adds an Entity to a group.
		* @param name - the name of the group
		* @param entity - the Entity to be added
		*/
		void																		addToGroup(const std::string& name, const Entity& entity);

		/**
		* Removes an Entity from all groups that it is in.
		* @param entity - the Entity to be removed
		*/
		void																		removeFromAllGroups(const Entity& entity);

		/**
		* Removes an Entity from a specific group.
		* @param name - the name of the group
		* @param entity - the Entity to be removed
		* @param fullErase - only true if Entity is being removed from all groups
		*/
		void																		removeFromGroup(const std::string& name, const Entity& entity, bool fullErase = false);

		/**
		* Retrieves all Entities from a group.
		* @param name - the name of the group
		* @return container of Entity::IDs that are in the group
		*/
		std::vector<Entity::ID>														getGroup(const std::string& name);

		/**
		* Retrieves all groups that an Entity is in.
		* @param entity - the Entity of interest.
		* @return container of named groups that the Entity is in.
		*/
		std::vector<std::string>													getEntityGroups(const Entity& entity) const;

		/**
		* Prints each group with the ID's of the Entities that are included.
		*/
		void																		toString();

	private:
		/** Holds a table organized as Group - Entities */
		std::unordered_map<std::string, 
			std::vector<Entity::ID>>												mGroupsByName;
		
		/** Holds a table organized as ID - Groups */
		std::vector<std::vector<std::string>>										mEntityGroups;
	};
}

