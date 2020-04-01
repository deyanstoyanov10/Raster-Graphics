#include "PBMImage.hpp"

PBMImage::PBMImage(const char* _path, const char* _magicNumber, unsigned int _rows, unsigned int _cols, unsigned int _colorMax)
	:Image(_path, _magicNumber, _rows, _cols, _colorMax)
{
	this->pixels = new int * [_rows];

	for (unsigned int i = 0; i < _rows; i++)
	{
		this->pixels[i] = new int[_cols];
	}
}

PBMImage::PBMImage(const PBMImage& image) : PBMImage()
{
	if (this != &image)
	{
		copy(image);
	}
}

PBMImage& PBMImage::operator=(const PBMImage& image)
{
	if (this != &image)
	{
		del();
		Image::operator=(image);
		copy(image);
	}

	return *this;
}

PBMImage::~PBMImage()
{
	del();
}

void PBMImage::load(std::istream& in)
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

void PBMImage::save(std::ostream& out)
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

void PBMImage::Negative()
{
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			pixels[i][j] = this->colorMax - pixels[i][j];
		}
	}
}

void PBMImage::copy(const PBMImage& image)
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
			this->pixels[i][j] = image.pixels[i][j];
		}
	}
}

void PBMImage::del()
{
	for (unsigned int i = 0; i < this->rows; i++)
		delete[] pixels[i];
	delete[] pixels;
}
