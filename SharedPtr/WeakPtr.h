#pragma once

#include <iostream>
#include "SharedPtr.h"

template <typename T>
class WeakPtr
{
private:
	T* pointer;
	size_t* counter;
	bool isArray;


	void Init(const WeakPtr& source);
	void Init(const SharedPtr<T>& source);

public:
	WeakPtr(const SharedPtr<T>& source);
	WeakPtr(const WeakPtr& source);
	WeakPtr(WeakPtr&& source) noexcept;

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
	counter = source.counter;
}

template <typename T>
void WeakPtr<T>::Init(const SharedPtr<T>& source)
{
	pointer = source.Get();
	isArray = source.GetIsArray();
	counter = source.GetCounter();
}


// Public methods

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& source) 
{
	Init(source);
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& source)
{
	Init(source);
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& source) noexcept
{
	Init(source);
	source.pointer = nullptr;
	source.isArray = false;
	source.counter = nullptr;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other)
{
	if (&other != this)
		Init(other);

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
		other.counter = nullptr;
	}

	return *this;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::Lock()
{
	return SharedPtr<T> { pointer, isArray, counter };
}
