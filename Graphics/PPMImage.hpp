#pragma warning( disable : 4996 )
#ifndef __PPMIMAGE_HPP
#define __PPMIMAGE_HPP

#include<iostream>
#include "Image.hpp"
#include "Pixel.hpp"

const double Red = 0.299;
const double Green = 0.587;
const double Blue = 0.114;

class PPMImage : public Image
{
public:
	PPMImage(const char* _path = "", const char* _magicNumber = "", unsigned int _rows = 0, unsigned int _cols = 0, unsigned int _colorMax = 0);
	PPMImage(const PPMImage& image);
	PPMImage& operator=(const PPMImage& image);
	~PPMImage();
public:
	Image* clone()
	{
		return new PPMImage(*this);
	}

	void load(std::istream& in) override;
	void save(std::ostream& out) override;
	
	void GrayScale() override;
	void Negative() override;
	void Rotate(const char* direction) override;
private:
	void rotateRight();
	void copy(const PPMImage& image);
	void del();

	bool CheckForGrayScaledImage();
private:
	Pixel** pixels;
};
#endif // !__PPMIMAGE_HPP
