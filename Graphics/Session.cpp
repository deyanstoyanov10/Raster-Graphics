#pragma warning(disable: 4996)
#include "Session.hpp"

Session::Session(unsigned int _sessionId, unsigned int _capacity, unsigned int _historyCapacity)
	: sessionId(_sessionId), capacity(_capacity), size(0), historyCapacity(_historyCapacity), historySize(0)
{
	this->images = new Image * [_capacity];
	this->history = new History[_historyCapacity];
}

Session::Session(const Session& session) : Session()
{
	if (this != &session)
	{
		copy(session);
	}
}

Session& Session::operator=(const Session& session)
{
	if (this != &session)
	{
		del();
		copy(session);
	}

	return *this;
}

Session::~Session()
{
	del();
}

void Session::addToHistory(const char* beforeChanges)
{
	if (historySize >= historyCapacity)
	{
		resizeHistory(historyCapacity * 2);
	}

	this->history[size].addToHistory(beforeChanges, this->images, this->size, this->capacity);
	this->historySize++;
}

void Session::copy(const Session& session)
{
	this->images = new Image * [session.capacity];
	
	for (unsigned int i = 0; i < session.size; i++)
	{
		this->images[i] = session.images[i]->clone();
	}
	
	this->history = new History[session.historyCapacity];

	for (unsigned int i = 0; i < session.historySize; i++)
	{
		this->history[i] = session.history[i];
	}

	this->sessionId = session.sessionId;
	this->capacity = session.capacity;
	this->size = session.size;
	this->historyCapacity = session.historyCapacity;
	this->historySize = session.historySize;
}

void Session::del()
{
	delete[] history;

	for (int i = 0; i < this->size; i++)
	{
		delete images[i];
	}
	delete[] images;
}

void Session::resize(unsigned int newCapacity)
{
	this->capacity = newCapacity;

	Image** newImages = new Image * [newCapacity];

	for (unsigned int i = 0; i < size; i++)
	{
		newImages[i] = this->images[i];
	}

	for (int i = 0; i < this->size; i++)
	{
		delete images[i];
	}
	delete[] images;

	this->images = newImages;
}

void Session::resizeHistory(unsigned int newHistoryCapacity)
{
	this->historyCapacity = newHistoryCapacity;

	History* newHistory = new History[newHistoryCapacity];

	for (unsigned int i = 0; i < size; i++)
	{
		newHistory[i] = this->history[i];
	}

	delete[] history;

	this->history = newHistory;
}

void Session::AddImage(Image* image)
{
	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	this->images[size] = image;

	std::cout << "Image ";
	image[size].PrintFileName();
	std::cout << " added" << std::endl;

	this->size++;
}

void Session::RemoveImage()
{
	this->size--;
}

void Session::ManipulateImages(const char* command)
{
	addToHistory(command);

	if (strcmp(command, "grayscale") == 0)
	{
		for (unsigned int i = 0; i < this->size; i++)
		{
			this->images[i]->GrayScale();
		}
	}
	else if (strcmp(command, "monochrome") == 0)
	{

	}
	else if (strcmp(command, "negative") == 0)
	{
		for (unsigned int i = 0; i < this->size; i++)
		{
			this->images[i]->Negative();
		}
	}
	else
	{
		throw std::exception("Invalid command");
	}
}

void Session::SessionInfo()
{
	std::cout << "Name of images in the session: ";
	for (unsigned int i = 0; i < size; i++)
	{
		images[i]->PrintFileName();
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "Pending transformations: ";

	for (unsigned int i = 0; i < historySize; i++)
	{
		this->history[i].PrintPendingChanges();
		if (i == historySize - 1)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ", ";
		}
	}
}

void Session::UndoLastChanges()
{
	if (this->historySize == 0)
	{
		throw std::exception("There are no any changes in this session for undo");
	}

	for (unsigned int i = 0; i < size; i++)
	{
		delete images[i];
	}
	delete[] images;

	this->images = new Image * [history[historySize].getCapacity()];

	Image** historyImages = history[historySize].getImages();
	for (unsigned int i = 0; i < history[historySize].getSize(); i++)
	{
		this->images[i] = historyImages[i]->clone();
	}

	this->size = history[historySize].getSize();
	this->capacity = history[historySize].getCapacity();
	
	this->historySize--;
}

void Session::RotateImages(const char* direction)
{
	addToHistory(direction);

	if (strcmp(direction, "left") != 0 && strcmp(direction, "right") != 0)
	{
		throw std::exception("Invalid command!");
	}

	for (unsigned int i = 0; i < size; i++)
	{
		this->images[i]->Rotate(direction);
	}
}
