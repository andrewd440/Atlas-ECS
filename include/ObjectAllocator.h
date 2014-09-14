#pragma once
#include "ICustomAllocator.h"
#include <cstdint>

class ObjectAllocator : public ICustomAllocator
{
public:
	explicit ObjectAllocator(size_t objectSize);
	ObjectAllocator(size_t objectSize, size_t numObjects);

	~ObjectAllocator();

	void* alloc();

	void* dealloc(void* p, size_t size);

	void* operator[](size_t index);

	const void* operator[](size_t index) const;

private:
	void* mObjects;
	uint32_t mObjectSize;
	uint32_t mSize;
	uint32_t mCapacity;
};

