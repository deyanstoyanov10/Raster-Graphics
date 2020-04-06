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

void PGMImage::saveas(const char* direction)
{
	std::fstream fout(direction, std::ios::out);

	if (!fout.is_open())
	{
		throw new std::exception("Cannot open file");
	}
	this->save(fout);

	fout.close();
}

void PGMImage::collageHorizontal(std::ostream& out, int index)
{
	for (unsigned int i = 0; i < cols; i++)
	{
		out << this->pixels[index][i];
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

void PGMImage::Rotate(const char* direction)
{
	if (strcmp(direction, "left") == 0)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			rotateRight();
		}
	}
	else if (strcmp(direction, "right") == 0)
	{
		rotateRight();
	}
	else
	{
		throw std::exception("Invalid command!");
	}
}

void PGMImage::rotateRight()
{
	int** newPixels = new int* [cols];
	for (unsigned int i = 0; i < cols; i++)
	{
		newPixels[i] = new int[rows];
	}

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			newPixels[j][i] = pixels[i][j];
		}
	}

	int temp = rows;
	this->rows = this->cols;
	this->cols = temp;

	for (unsigned int i = 0; i < cols; i++)
	{
		int* arrTemp = new int[rows];
		for (unsigned int j = 0; j < rows; j++)
		{
			arrTemp[j] = newPixels[i][j];
		}

		for (unsigned index = 0; index < rows; index++)
		{
			newPixels[i][index] = arrTemp[rows - 1 - index];
		}
	}

	for (unsigned int i = 0; i < cols; i++)
		delete[] pixels[i];
	delete[] pixels;

	this->pixels = newPixels;
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