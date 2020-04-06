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

void Session::compareImages(const char* firstImage, const char* secondImage, int& indexOne, int& indexTwo)
{
	bool checkOne = false;
	bool checkTwo = false;
	int firstIndex = 0, secondIndex = 0;

	for (unsigned int i = 0; i < size; i++)
	{
		if (strcmp(this->images[i]->getFileName(), firstImage) == 0)
		{
			firstIndex = i;
			checkOne = true;
			break;
		}
	}

	
	for (unsigned int i = 0; i < size; i++)
	{
		if (strcmp(this->images[i]->getFileName(), secondImage) == 0)
		{
			secondIndex = i;
			checkTwo = true;
			break;
		}
	}

	indexOne = firstIndex;
	indexTwo = secondIndex;

	if (checkOne == false || checkTwo == false)
	{
		throw std::exception("Images doesn't exist");
	}

	if (strcmp(this->images[firstIndex]->getMagicNumber(), this->images[secondIndex]->getMagicNumber()) != 0)
	{
		throw std::exception("Images doesn't match");
	}

	if ((this->images[firstIndex]->getRows() != this->images[secondIndex]->getRows()) || (this->images[firstIndex]->getCols() != this->images[secondIndex]->getCols()))
	{
		throw std::exception("Images size doesn't match");
	}
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

void Session::MakeCollage(const char* direction, const char* firstImage, const char* secondImage, const char* outImage)
{
	int indexOne = 0;
	int indexTwo = 0;

	if (strcmp(direction, "horizontal") == 0)
	{
		compareImages(firstImage, secondImage, indexOne, indexTwo);
		std::fstream fout(direction, std::ios::out);

		if (!fout.is_open())
		{
			throw new std::exception("Cannot open file");
		}
		const char* magicNumber = this->images[indexOne]->getMagicNumber();
		for (unsigned int i = 0; i < strlen(magicNumber); i++)
		{
			fout << magicNumber[i];
		}
		fout << std::endl;
		fout << this->images[indexOne]->getCols() + this->images[indexTwo]->getCols() << " " << this->images[indexOne]->getRows() << std::endl;
		fout << this->images[indexOne]->getColorMax() << std::endl;

		for (unsigned int i = 0; i < this->images[indexOne]->getRows(); i++)
		{
			this->images[indexOne]->collageHorizontal(fout, i);
			this->images[indexTwo]->collageHorizontal(fout, i);
			fout << std::endl;
		}
		fout.close();
	}
	else if (strcmp(direction, "vertical") == 0)
	{
		compareImages(firstImage, secondImage, indexOne, indexTwo);
		std::fstream fout(direction, std::ios::out);

		if (!fout.is_open())
		{
			throw new std::exception("Cannot open file");
		}

		const char* magicNumber = this->images[indexOne]->getMagicNumber();
		for (unsigned int i = 0; i < strlen(magicNumber); i++)
		{
			fout << magicNumber[i];
		}
		fout << std::endl;
		fout << this->images[indexOne]->getCols()<< " " << this->images[indexOne]->getRows() + this->images[indexTwo]->getRows() << std::endl;
		fout << this->images[indexOne]->getColorMax() << std::endl;

		this->images[indexOne]->save(fout);
		this->images[indexTwo]->save(fout);

		fout.close();
	}
	else
	{
		throw std::exception("Invalid command");
	}
}
