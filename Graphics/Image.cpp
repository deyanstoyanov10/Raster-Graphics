#pragma warning(disable: 4996)
#include "Image.hpp"

Image::Image(const char* _path, const char* _magicNumber, unsigned int _rows, unsigned int _cols, unsigned int _colorMax)
	:rows(_rows), cols(_cols), colorMax(_colorMax)
{
	setPath(_path);
	setMagicNumber(_magicNumber);
}

//Image::Image(const Image& image) : Image()
//{
//	if (this != &image)
//	{
//		copy(image);
//	}
//}
//
//Image& Image::operator=(const Image& image)
//{
//	if (this != &image)
//	{
//		del();
//		copy(image);
//	}
//	return *this;
//}

Image::~Image()
{
	del();
}

Image* Image::clone()
{
	return nullptr;
}

void Image::setPath(const char* path)
{
	if (path == nullptr)
	{
		this->path = new char[1];
		strcpy(this->path, "");
		return;
	}
	this->path = new char[strlen(path) + 1];
	strcpy(this->path, path);
}

void Image::setMagicNumber(const char* magicNumber)
{
	if (magicNumber == nullptr)
	{
		this->magicNumber = new char[1];
		strcpy(this->magicNumber, "");
		return;
	}

	this->magicNumber = new char[strlen(magicNumber) + 1];
	strcpy(this->magicNumber, magicNumber);
}

void Image::PrintFileName()
{
	const char* path = this->getPath();
	int index = 0;
	int pathLength = strlen(path);

	for (int i = pathLength - 1; i >= 0; i--)
	{
		if (path[i] == '\\' || path[i] == '/')
		{
			break;
		}
		index = i;
	}

	while (path[index])
	{
		std::cout << path[index];
		index++;
	}
}

void Image::load(std::istream& in)
{
}

void Image::save(std::ostream& out)
{
}

void Image::GrayScale()
{
}

void Image::Monochrome()
{
}

void Image::Negative()
{
}

void Image::copy(const Image& image)
{
	setPath(image.path);
	setMagicNumber(image.magicNumber);

	this->rows = image.rows;
	this->cols = image.cols;
	this->colorMax = image.colorMax;
}

void Image::del()
{
	delete[] path;
	delete[] magicNumber;
}
