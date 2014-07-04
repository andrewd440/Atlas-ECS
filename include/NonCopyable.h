#pragma once

namespace Atlas
{
	/**
	* Base class for objects not intended to be copied.
	*/
	class NonCopyable
	{
	public:
		/** Default Constructor */
		NonCopyable() = default;

		virtual ~NonCopyable()
		{
		}

	private:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable&										operator=(const NonCopyable&) = delete;
	};
}