#include "ComponentIdentifierManager.h"
#include "ComponentIdentifier.h"

namespace Atlas
{
	ComponentIdentifier& ComponentIdentifierManager::getType(const std::type_index& index)
	{
		// If an identifier is not assigned, assign one
		if (ComponentMap[index] == nullptr)
		{
			ComponentIdentifier::Ptr id(new ComponentIdentifier());
			ComponentMap[index] = std::move(id);
		}

		return *ComponentMap[index];
	}

	std::unordered_map <std::type_index, ComponentIdentifier::Ptr> ComponentIdentifierManager::ComponentMap;
}