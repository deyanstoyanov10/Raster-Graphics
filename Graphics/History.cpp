#pragma warning(disable: 4996)
#include "History.hpp"

History::History(const char* changesBefore)
	:size(0), capacity(1)
{
	this->changesBefore = new char[strlen(changesBefore) + 1];
	strcpy(this->changesBefore, changesBefore);

	this->imagesHistory = new Image * [capacity];
}

History::History(const History& history)
{
	if (this != &history)
	{
		copy(history);
	}
}

History& History::operator=(const History& history)
{
	if (this != &history)
	{
		del();
		copy(history);
	}
	return *this;
}

History::~History()
{
	del();
}

void History::addToHistory(const char* changesBefore, Image** images, unsigned int size, unsigned int capacity)
{
	del();

	this->changesBefore = new char[strlen(changesBefore) + 1];
	strcpy(this->changesBefore, changesBefore);

	this->size = size;
	this->capacity = capacity;

	this->imagesHistory = new Image * [capacity];

	for (unsigned int i = 0; i < size; i++)
	{
		this->imagesHistory[i] = images[i]->clone();
	}
}

void History::PrintPendingChanges()
{
	std::cout << changesBefore << std::endl;
}

void History::copy(const History& history)
{
	this->changesBefore = new char[strlen(history.changesBefore) + 1];
	strcpy(changesBefore, history.changesBefore);

	this->capacity = history.capacity;
	this->size = history.size;

	this->imagesHistory = new Image * [history.capacity];
	for (unsigned int i = 0; i < history.size; i++)
	{
		this->imagesHistory[i] = history.imagesHistory[i]->clone();
	}
}

void History::del()
{
	delete[] changesBefore;

	for (unsigned int i = 0; i < size; i++)
	{
		delete imagesHistory[i];
	}
	delete[] imagesHistory;
}