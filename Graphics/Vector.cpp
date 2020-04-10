#include "Vector.hpp"

template<class Type>
inline Vector<Type>::Vector(unsigned int _capacity)
	:capacity(_capacity),size(0)
{
	this->container = new Type[_capacity];
}

template<class Type>
Vector<Type>::Vector(const Vector& vector) : Vector()
{
	if (this != &vector)
	{
		this->container = new Type[vector.capacity];

		for (unsigned int i = 0; i < vector.size; i++)
		{
			this->container[i] = vector.container[i];
		}

		this->capacity = vector.capacity;
		this->size = vector.size;
	}
}

template<class Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& vector)
{
	if (this != &vector)
	{
		del();
		this->container = new Type[vector.capacity];

		for (unsigned int i = 0; i < vector.capacity; i++)
		{
			this->container[i] = vector.container[i];
		}

		this->capacity = vector.capacity;
		this->size = vector.size;
	}

	return *this;
}

template<class Type>
Vector<Type>::~Vector()
{
	del();
}

template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::begin()
{
	return Vector<Type>::iterator(&container[0]);
}

template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::end()
{
	return Vector<Type>::iterator(&container[size]);
}

template<class Type>
inline typename const Vector<Type>::iterator Vector<Type>::begin() const
{
	return Vector<Type>::iterator(&container[0]);
}

template<class Type>
inline typename const Vector<Type>::iterator Vector<Type>::end() const
{
	return Vector<Type>::iterator(&container[size]);
}

template<class Type>
const unsigned int Vector<Type>::count() const
{
	return this->size;
}

template<class Type>
void Vector<Type>::push_back(Type type)
{
	if (size >= capacity)
	{
		resize(capacity * 2);
	}
	this->container[size++] = type;
}

template<class Type>
void Vector<Type>::pop_back()
{
	if (size > 0)
	{
		this->size--;
	}
}

template<class Type>
Type Vector<Type>::at(unsigned int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}
	return this->container[index];
}

template<class Type>
Type& Vector<Type>::at(unsigned int index)
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}
	return this->container[index];
}

template<class Type>
Type Vector<Type>::operator[](unsigned int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}
	return this->container[index];
}

template<class Type>
Type& Vector<Type>::operator[](unsigned int index)
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}
	return this->container[index];
}

template<class Type>
void Vector<Type>::del()
{
	delete[] container;
}

template<class Type>
void Vector<Type>::resize(unsigned int newCapacity)
{
	this->capacity = newCapacity;
	Type* newContainer = new Type[newCapacity];

	for (unsigned int i = 0; i < size; i++)
	{
		newContainer[i] = container[i];
	}
	
	del();
	this->container = newContainer;
}