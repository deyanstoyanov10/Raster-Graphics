#pragma once

#include<iostream>
#define MAX_CAPACITY 20

template<class Type>
class Vector
{
public:
	Vector(unsigned int _capacity = MAX_CAPACITY);
	Vector(const Vector& vector);
	Vector<Type>& operator=(const Vector<Type>& vector);
	~Vector();

	class iterator;
	iterator begin();
	iterator end();
	const iterator begin() const;
	const iterator end() const;

	const unsigned int count() const;
	void push_back(Type type);
	void pop_back();
	Type at(unsigned int index) const;
	Type& at(unsigned int index);
	Type operator[](unsigned int index) const;
	Type& operator[](unsigned int index);
private:
	void del();
	void resize(unsigned int newCapacity);
private:
	Type* container;
	unsigned int capacity;
	unsigned int size;
};

template<class Type>
class Vector<Type>::iterator
{
public:
	iterator(Type* _current) : current(_current) {}
	iterator& operator++()
	{
		current++;
		return *this;
	}

	iterator& operator--()
	{
		current--;
		return *this;
	}

	Type& operator*()
	{
		return *current;
	}

	bool operator==(const iterator& it) const
	{
		return *current == *it.current;
	}

	bool operator!=(const iterator& it) const
	{
		return *current != *it.current;
	}
private:
	Type* current;
};