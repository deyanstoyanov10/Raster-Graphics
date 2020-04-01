#ifndef __HISTORY_HPP
#define __HISTORY_HPP

#include "Image.hpp"

class History
{
public:
	History(const char* changesBefore="");
	History(const History& history);
	History& operator=(const History& history);
	~History();
public:
	Image** getImages() const { return this->imagesHistory; }
	int getSize() const { return this->size; }
	int getCapacity() const { return this->capacity; }

	void addToHistory(const char* changesBefore, Image** images, unsigned int size, unsigned int capacity);
	void PrintPendingChanges();
private:
	void copy(const History& history);
	void del();
private:
	char* changesBefore;
	Image** imagesHistory;
	unsigned int size;
	unsigned int capacity;
};

#endif // !__HISTORY_HPP