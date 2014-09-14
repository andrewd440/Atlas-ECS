#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace Atlas
{
	template <typename T>
	/**
	* Converts objects to strings
	* @param value - object to be converted
	* @return converted string from the object
	*/
	std::string to_String(const T& value)
	{
		std::stringstream stream;
		stream << value;
		return stream.str();
	}

	template <typename T>
	/**
	* Removes class/struct string from typeid::name() for cleaner print formatting
	* Usage Example:
	~~~~~~~~~~~~~~~~
	* HealthSystem* system;
	* cout << "This is a " << typeidStringFormator(HealthSystem);
	* Output : This is a HealthSystem
	~~~~~~~~~~~~~~~~
	* @param object - the object
	* @return string of the object type
	*/
	std::string typeidStringFormator(const T* object)
	{
		std::string str;
		const auto& po = typeid(*object).name();

		for (int i = 6; po[i] != NULL; i++)
			str.push_back(po[i]);

		return str;
	}
}