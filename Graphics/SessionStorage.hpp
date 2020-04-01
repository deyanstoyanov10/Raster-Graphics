#ifndef __SESSIONSTORRAGE_HPP
#define __SESSIONSTORRAGE_HPP

#include "Session.hpp"

#define MAX_CAPACITY 10

class SessionStorage
{
public:
	SessionStorage(unsigned int _capacity = MAX_CAPACITY);
	SessionStorage(const SessionStorage& storage);
	SessionStorage& operator=(const SessionStorage& storage);
	~SessionStorage();
public:
	void AddSession(Session session);
	void RemoveImage(int sessionIndex);
	int GetSessionId (unsigned int index) const;
	
	int getIndex() const { return this->currentIndex; }
	Session* getSession() const { return this->sessionStorage; }
private:
	void copy(const SessionStorage& storage);
	void del();

	void resize(unsigned int newCapacity);
private:
	Session* sessionStorage;
	unsigned int currentIndex;
	unsigned int capacity;
};
#endif // !__SESSIONSTORRAGE_HPP
