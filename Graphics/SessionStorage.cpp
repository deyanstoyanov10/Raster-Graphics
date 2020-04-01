#include "SessionStorage.hpp"

SessionStorage::SessionStorage(unsigned int _capacity)
	:currentIndex(0), capacity(_capacity)
{
	this->sessionStorage = new Session[_capacity];
}

SessionStorage::SessionStorage(const SessionStorage& storage) : SessionStorage()
{
	if (this != &storage)
	{
		copy(storage);
	}
}

SessionStorage& SessionStorage::operator=(const SessionStorage& storage)
{
	if (this != &storage)
	{
		del();
		copy(storage);
	}
	return *this;
}

SessionStorage::~SessionStorage()
{
	del();
}

void SessionStorage::copy(const SessionStorage& storage)
{
	this->sessionStorage = new Session[storage.capacity];

	for (unsigned int i = 0; i < storage.currentIndex; i++)
	{
		this->sessionStorage[i] = storage.sessionStorage[i];
	}

	this->currentIndex = storage.currentIndex;
	this->capacity = storage.capacity;
}

void SessionStorage::del()
{
	delete[] sessionStorage;
}

void SessionStorage::resize(unsigned int newCapacity)
{
	this->capacity = newCapacity;
	Session* newSessionStorage = new Session[newCapacity];

	for (unsigned int i = 0; i < currentIndex; i++)
	{
		newSessionStorage[i] = this->sessionStorage[i];
	}

	del();
	this->sessionStorage = newSessionStorage;
}

void SessionStorage::AddSession(Session session)
{
	if (currentIndex >= capacity)
	{
		resize(capacity * 2);
	}
	this->sessionStorage[currentIndex] = session;
	this->currentIndex++;
}

void SessionStorage::RemoveImage(int sessionIndex)
{
	this->sessionStorage[sessionIndex].RemoveImage();
}

int SessionStorage::GetSessionId(unsigned int index) const
{
	return this->sessionStorage[index].getSessionId();
}