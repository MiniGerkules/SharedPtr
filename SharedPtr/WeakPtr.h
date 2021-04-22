#pragma once

#include <iostream>
#include "SharedPtr.h"

template <typename T>
class WeakPtr
{
private:
	T* pointer;
	std::vector<SharedPtr<T>*> allSharedPtr;
	bool isArray;


	void Init(const WeakPtr& source);

public:
	WeakPtr(SharedPtr<T>& source);
	WeakPtr(const WeakPtr& source);
	WeakPtr(WeakPtr&& source);

	WeakPtr& operator=(const WeakPtr& other);
	WeakPtr& operator=(WeakPtr&& other);

	WeakPtr& operator*() const = delete;
	WeakPtr* operator->() const = delete;

	SharedPtr<T> Lock();
};


//  Private methods

template <typename T>
void WeakPtr<T>::Init(const WeakPtr& source)
{
	pointer = source.pointer;
	isArray = source.isArray;
	allSharedPtr.insert(allSharedPtr.end(), source.allSharedPtr.begin(), source.allSharedPtr.end());
}


// Public methods

template <typename T>
WeakPtr<T>::WeakPtr(SharedPtr<T>& source)
	: pointer(source.Get()), isArray(source.GetIsArray())
{
	allSharedPtr.insert(allSharedPtr.end(), source.GetAllSharedPtr().begin(), source.GetAllSharedPtr().end());
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& source)
	: pointer(source.pointer), isArray(source.isArray)
{
	allSharedPtr.insert(allSharedPtr.end(), source.allSharedPtr.begin(), source.allSharedPtr.end());
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& source)
{
	Init(source);
	source.pointer = nullptr;
	source.isArray = false;
	source.allSharedPtr.clear();
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other)
{
	if (&other != this)
	{
		allSharedPtr.clear();
		Init(other);
	}

	return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& other)
{
	if (&other != this)
	{
		Init(other);
		other.pointer = nullptr;
		other.isArray = false;
		other.allSharedPtr.clear();
	}

	return *this;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::Lock()
{
	return SharedPtr<T> { pointer, isArray, allSharedPtr };
}
