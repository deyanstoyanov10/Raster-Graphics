#pragma warning(disable: 4996)
#include "Session.hpp"

Session::Session(unsigned int _sessionId, unsigned int _capacity)
	: sessionId(_sessionId), capacity(_capacity), size(0)
{
	this->images = new Image * [_capacity];
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

void Session::copy(const Session& session)
{
	this->images = new Image * [session.capacity];
	
	for (unsigned int i = 0; i < session.size; i++)
	{
		this->images[i] = session.images[i]->clone();
	}
	
	this->sessionId = session.sessionId;
	this->capacity = session.capacity;
	this->size = session.size;
}

void Session::del()
{
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

	del();
	this->images = newImages;
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
}
