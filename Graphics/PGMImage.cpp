#include "PGMImage.hpp"

PGMImage::PGMImage(const char* _path, const char* _magicNumber, unsigned int _rows, unsigned int _cols, unsigned int _colorMax)
	:Image(_path, _magicNumber, _rows, _cols, _colorMax)
{
	this->pixels = new int* [_rows];

	for (unsigned int i = 0; i < _rows; i++)
	{
		this->pixels[i] = new int[_cols];
	}
}

PGMImage::PGMImage(const PGMImage& image) : PGMImage()
{
	if (this != &image)
	{
		copy(image);
	}
}

PGMImage& PGMImage::operator=(const PGMImage& image)
{
	if (this != &image)
	{
		del();
		copy(image);
	}

	return *this;
}

PGMImage::~PGMImage()
{
	del();
}

void PGMImage::load(std::istream& in)
{
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			if (in.good())
			{
				in >> pixels[i][j];
			}
		}
	}
}

void PGMImage::save(std::ostream& out)
{
	const char* magicNumber = this->magicNumber;
	for (unsigned int i = 0; i < strlen(magicNumber); i++)
	{
		out << magicNumber[i];
	}
	out << std::endl;
	out << this->cols << " " << this->rows << std::endl;
	out << this->colorMax << std::endl;

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{

			if (j != this->cols - 1)
			{
				out << pixels[i][j] << " ";
			}
			else
			{
				out << pixels[i][j];
			}

		}
		out << std::endl;
	}
}

void PGMImage::Negative()
{
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			pixels[i][j] = this->colorMax - pixels[i][j];
		}
	}
}

void PGMImage::copy(const PGMImage& image)
{
	this->setPath(image.path);
	this->setMagicNumber(image.magicNumber);

	this->rows = image.rows;
	this->cols = image.cols;
	this->colorMax = image.colorMax;

	this->pixels = new int* [image.rows];
	for (unsigned int i = 0; i < image.rows; i++)
	{
		this->pixels[i] = new int[image.cols];
	}

	for (unsigned int i = 0; i < image.rows; i++)
	{
		for (unsigned int j = 0; j < image.cols; j++)
		{
			pixels[i][j] = image.pixels[i][j];
		}
	}
}

void PGMImage::del()
{
	for (unsigned int i = 0; i < this->rows; i++)
		delete[] pixels[i];
	delete[] pixels;
}