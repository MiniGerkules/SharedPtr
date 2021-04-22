#pragma once

#include <iostream>
#include <vector>

template <typename T>
class SharedPtr
{
private:
	T* pointer;
	std::vector<SharedPtr*> allSharedPtr;
	bool isArray;


	void Init(SharedPtr& other);

	size_t FindInOther(const SharedPtr* const other);
	void DeleteInOthers();

public:
	SharedPtr();
	SharedPtr(T* pointer, bool isArray, std::vector<SharedPtr*> allSharedPtr = std::vector<SharedPtr*>());
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
	std::vector<SharedPtr*>& GetAllSharedPtr();
};


// Private methods

template <typename T>
void SharedPtr<T>::Init(SharedPtr& other)
{
	pointer = other.pointer;
	isArray = other.isArray;
	allSharedPtr.insert(allSharedPtr.end(), other.allSharedPtr.begin(), other.allSharedPtr.end());
	allSharedPtr.push_back(&other);
	for (SharedPtr* ptr : allSharedPtr)
		ptr->allSharedPtr.push_back(this);
}

template <typename T>
size_t SharedPtr<T>::FindInOther(const SharedPtr* const other)
{
	for (size_t i = 0; i < other->allSharedPtr.size(); ++i)
		if (other->allSharedPtr[i] == this)
			return i;

	throw std::out_of_range("The pointer doesn't exist!");
}

template <typename T>
void SharedPtr<T>::DeleteInOthers()
{
	if (pointer != nullptr)
	{
		if (allSharedPtr.size() == 0)
		{
			if (isArray)
				delete[] pointer;
			else
				delete pointer;
		}
		else
		{
			size_t indexOfPtr;

			for (SharedPtr* ptr : allSharedPtr)
			{
				try
				{
					indexOfPtr = FindInOther(ptr);
					ptr->allSharedPtr.erase(ptr->allSharedPtr.begin() + indexOfPtr);
				}
				catch (std::out_of_range error)
				{
					std::cerr << error.what() << std::endl;
				}
			}
		}

		pointer = nullptr;
		isArray = false;
		allSharedPtr.clear();
	}
}


// Public methods

template <typename T>
SharedPtr<T>::SharedPtr()
	: pointer(nullptr), isArray(false)
{
}

template <typename T>
SharedPtr<T>::SharedPtr(T* pointer, bool isArray, std::vector<SharedPtr*> allSharedPtr)
	: pointer(pointer), isArray(isArray)
{
	this->allSharedPtr = std::move(allSharedPtr);
	for (SharedPtr* ptr : this->allSharedPtr)
		ptr->allSharedPtr.push_back(this);
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
	other.pointer = nullptr;
	other.isArray = false;

	allSharedPtr = std::move(other.allSharedPtr);
	for (SharedPtr* ptr : allSharedPtr)
		for (size_t i = 0; i < ptr->allSharedPtr.size(); ++i)
			if (ptr->allSharedPtr[i] == &other)
				ptr->allSharedPtr[i] = this;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
	DeleteInOthers();
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
			DeleteInOthers();
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
		{
			Init(other);
			other.DeleteInOthers();
		}
		else
		{
			DeleteInOthers();
			Init(other);
			other.DeleteInOthers();
		}
	}

	return *this;
}

template <typename T>
size_t SharedPtr<T>::UseCount() const
{
	if (pointer == nullptr)
		return 0;
	else
		return allSharedPtr.size() + 1;
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
std::vector<SharedPtr<T>*>& SharedPtr<T>::GetAllSharedPtr()
{
	return allSharedPtr;
}
