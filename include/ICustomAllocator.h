#pragma once
class ICustomAllocator
{
public:

	virtual ~ICustomAllocator() {};

	virtual void* alloc() = 0;

	virtual void* dealloc(void* p, size_t size) = 0;

	virtual void* operator[](size_t index) = 0;

	virtual const void* operator[](size_t index) const = 0;
};

