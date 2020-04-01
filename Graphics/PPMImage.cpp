#include "PPMImage.hpp"

PPMImage::PPMImage(const char* _path, const char* _magicNumber, unsigned int _rows, unsigned int _cols, unsigned int _colorMax)
	:Image(_path, _magicNumber, _rows, _cols, _colorMax)
{
	this->pixels = new Pixel* [_rows];

	for (unsigned int i = 0; i < _rows; i++)
	{
		this->pixels[i] = new Pixel[_cols];
	}
}

PPMImage::PPMImage(const PPMImage& image) : PPMImage()
{
	if (this != &image)
	{
		copy(image);
	}
}

PPMImage& PPMImage::operator=(const PPMImage& image)
{
	if (this != &image)
	{
		del();
		copy(image);
	}
	return *this;
}

PPMImage::~PPMImage()
{
	del();
}

void PPMImage::load(std::istream& in)
{
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			if (in.good())
			{
				in >> pixels[i][j].red >> pixels[i][j].green >> pixels[i][j].blue;
			}
		}
	}
}

void PPMImage::save(std::ostream& out)
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
				out << pixels[i][j].red << " " << pixels[i][j].green << " " << pixels[i][j].blue << " ";
			}
			else
			{
				out << pixels[i][j].red << " " << pixels[i][j].green << " " << pixels[i][j].blue;
			}
			
		}
		out << std::endl;
	}
}

void PPMImage::GrayScale()
{
	/*if (CheckForGrayScaledImage() == true)
	{
		this->PrintFileName();
		std::cout << " is already grayscaled" << std::endl;
		return;
	}*/

	unsigned int oldRed = 0;
	unsigned int oldGreen = 0;
	unsigned int oldBlue = 0;

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			oldRed = pixels[i][j].red;
			oldGreen = pixels[i][j].green;
			oldBlue = pixels[i][j].blue;

			pixels[i][j].red = (oldRed * Red) + (oldGreen * Green) + (oldBlue * Blue);
			pixels[i][j].green = (oldRed * Red) + (oldGreen * Green) + (oldBlue * Blue);
			pixels[i][j].blue = (oldRed * Red) + (oldGreen * Green) + (oldBlue * Blue);
		}
	}
}

void PPMImage::Negative()
{
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			pixels[i][j].red = this->colorMax - pixels[i][j].red;
			pixels[i][j].green = this->colorMax - pixels[i][j].green;
			pixels[i][j].blue = this->colorMax - pixels[i][j].blue;
		}
	}
}

void PPMImage::copy(const PPMImage& image)
{
	this->setPath(image.path);
	this->setMagicNumber(image.magicNumber);

	this->rows = image.rows;
	this->cols = image.cols;
	this->colorMax = image.colorMax;

	this->pixels = new Pixel * [image.rows];
	for (unsigned int i = 0; i < image.rows; i++)
	{
		this->pixels[i] = new Pixel[this->cols];
	}

	for (unsigned int i = 0; i < image.rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			pixels[i][j].red = image.pixels[i][j].red;
			pixels[i][j].green = image.pixels[i][j].green;
			pixels[i][j].blue = image.pixels[i][j].blue;
		}
	}
}

void PPMImage::del()
{
	for (unsigned int i = 0; i < this->rows; i++)
		delete[] pixels[i];
	delete[] pixels;
}

bool PPMImage::CheckForGrayScaledImage()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (pixels[i][j].red == pixels[i][j].green == pixels[i][j].blue)
			{
				return true;
			}
		}
	}

	return false;
}
