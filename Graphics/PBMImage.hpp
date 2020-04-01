#pragma warning( disable : 4996 )
#ifndef __PBMIMAGE_HPP
#define __PBMIMAGE_HPP

#include "Image.hpp"

class PBMImage : public Image
{
public:
	PBMImage(const char* _path = "", const char* _magicNumber = "", unsigned int _rows = 0, unsigned int _cols = 0, unsigned int _colorMax = 0);
	PBMImage(const PBMImage& image);
	PBMImage& operator=(const PBMImage& image);
	~PBMImage();
public:
	Image* clone()
	{
		return new PBMImage(*this);
	}
	void load(std::istream& in) override;
	void save(std::ostream& out) override;

	void Negative() override;
	void Rotate(const char* direction) override;
private:
	void rotateRight();
	void copy(const PBMImage& image);
	void del();
private:
	int** pixels;
};
#endif // !__PBMIMAGE_HPP
