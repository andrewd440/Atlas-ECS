#pragma once
#include <memory>

namespace Atlas
{
	/**
	* Base class for all Components
	*/
	class Component
	{
	public:
		/** Pointer for Component objects */
		typedef std::unique_ptr<Component> Ptr;

		/** Default Constructor */
		Component();

		/** Virtual Destructor */
		virtual	~Component();
	};
}