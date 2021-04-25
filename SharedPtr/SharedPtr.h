#pragma once

#include <iostream>
#include <vector>

template <typename T>
class SharedPtr
{
private:
	T* pointer;
	size_t* counter;
	bool isArray;


	void Init(SharedPtr& other);

public:
	SharedPtr();
	SharedPtr(T* pointer, bool isArray, size_t* counter = nullptr);
	SharedPtr(SharedPtr& other);
	SharedPtr(SharedPtr&& other) noexcept;

	~SharedPtr();

	const T& operator*() const;
	const T* operator->() const;
	SharedPtr& operator=(SharedPtr& other);
	SharedPtr& operator=(SharedPtr&& other);

	size_t UseCount() const;
	T* Get() const;
	bool GetIsArray() const;
	size_t* GetCounter() const;
};


// Private methods

template <typename T>
void SharedPtr<T>::Init(SharedPtr& other)
{
	pointer = other.pointer;
	isArray = other.isArray;
	counter = other.counter;
	++(*counter);
}


// Public methods

template <typename T>
SharedPtr<T>::SharedPtr()
	: pointer(nullptr), isArray(false)
{
}

template <typename T>
SharedPtr<T>::SharedPtr(T* pointer, bool isArray, size_t* counter)
	: pointer(pointer), isArray(isArray)
{
	if (counter == nullptr)
		this->counter = new size_t(1);
	else
		this->counter = counter;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr& other)
{
	Init(other);
}


template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept
{
	pointer = other.pointer;
	isArray = other.isArray;
	counter = other.counter;
	
	other.pointer = nullptr;
	other.isArray = false;
	other.counter = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
	if (pointer != nullptr)
	{
		if (*counter != 1)
			--(*counter);
		else
		{
			if (isArray)
				delete[] pointer;
			else
				delete pointer;

			delete counter;
		}
	}
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
	return *pointer;
}

template <typename T> 
const T* SharedPtr<T>::operator->() const 
{ 
	return pointer; 
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& other)
{
	if (&other != this)
	{
		if (pointer == nullptr)
			Init(other);
		else
		{
			--(*counter);
			Init(other);
		}
	}

	return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other)
{
	if (&other != this)
	{
		if (pointer == nullptr)
			Init(other);
		else
		{
			--(*counter);
			Init(other);
		}

		--(*other.counter);
		other.pointer = nullptr;
		other.isArray = false;
		other.counter = nullptr;
	}

	return *this;
}

template <typename T>
size_t SharedPtr<T>::UseCount() const
{
	if (pointer == nullptr)
		return 0;
	else
		return *counter;
}

template <typename T>
T* SharedPtr<T>::Get() const
{
	return pointer;
}

template <typename T>
bool SharedPtr<T>::GetIsArray() const
{
	return isArray;
}

template <typename T>
size_t* SharedPtr<T>::GetCounter() const
{
	return counter;
}
