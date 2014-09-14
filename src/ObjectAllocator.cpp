#include "ObjectAllocator.h"
#include <cstdlib>

ObjectAllocator::ObjectAllocator(size_t objectSize)
	: mObjects(nullptr)
	, mObjectSize(objectSize)
	, mSize(0)
	, mCapacity(0)
{
	
}


ObjectAllocator::ObjectAllocator(size_t objectSize, size_t numObjects)
	: mObjects(malloc(objectSize * numObjects))
	, mObjectSize(objectSize)
	, mSize(0)
	, mCapacity(numObjects)
{

}


ObjectAllocator::~ObjectAllocator()
{

}


void* ObjectAllocator::alloc()
{
	return (char *)mObjects + mObjectSize * mSize++;
}


void* ObjectAllocator::dealloc(void* p, size_t size)
{
	return mObjects;
}


void* ObjectAllocator::operator[](size_t index)
{
	return (char *)mObjects + index * mObjectSize;
}


const void* ObjectAllocator::operator[](size_t index) const
{
	return (char *)mObjects + index * mObjectSize;
}