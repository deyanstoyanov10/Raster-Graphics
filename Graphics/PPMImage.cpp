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

PPMImage::PPMImage(const PPMImage& image) : Image(image)
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
		Image::operator=(image);
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
	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			if (out.good())
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
		}
		out << std::endl;
	}
}

void PPMImage::saveas(const char* direction)
{
	std::fstream fout(direction, std::ios::out);
	
	if (!fout.is_open())
	{
		throw new std::exception("Cannot open file");
	}

	const char* magicNumber = this->magicNumber;
	fout << magicNumber << std::endl;
	fout << this->cols << " " << this->rows << std::endl;
	fout << this->colorMax << std::endl;
	this->save(fout);

	fout.close();
}

void PPMImage::collageHorizontal(std::ostream& out, int index)
{
	for (unsigned int i = 0; i < cols; i++)
	{
		if (out.good())
		{
			if (i != this->cols - 1)
			{
				out << pixels[index][i].red << " " << pixels[index][i].green << " " << pixels[index][i].blue << " ";
			}
			else
			{
				out << pixels[index][i].red << " " << pixels[index][i].green << " " << pixels[index][i].blue;
			}
		}
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

void PPMImage::Monochrome()
{
	unsigned short threshold = this->thresHold();

	int pix = 0;

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			unsigned short sum = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;

			if (sum >= threshold)
			{
				pix = colorMax;
			}

			pixels[i][j].red = pix;
			pixels[i][j].green = pix;
			pixels[i][j].blue = pix;

			pix = 0;
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

void PPMImage::Rotate(const char* direction)
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

unsigned short PPMImage::thresHold()
{
	unsigned int sum = 0;

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			int avg = pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue;
			sum += avg / 3;
		}
	}

	unsigned short threshold = sum / (rows * cols);

	return threshold;
}

void PPMImage::rotateRight()
{
	Pixel** newPixels = new Pixel * [cols];
	for (unsigned int i = 0; i < cols; i++)
	{
		newPixels[i] = new Pixel[rows];
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
		Pixel* arrTemp = new Pixel[rows];
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

void PPMImage::copy(const PPMImage& image)
{
	/*this->setPath(image.path);
	this->setMagicNumber(image.magicNumber);

	this->rows = image.rows;
	this->cols = image.cols;
	this->colorMax = image.colorMax;*/

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
