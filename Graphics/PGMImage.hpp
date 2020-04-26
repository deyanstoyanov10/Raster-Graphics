#pragma warning( disable : 4996 )
#ifndef __PGMIMAGE_HPP
#define __PGMIMAGE_HPP

#include "Image.hpp"

class PGMImage : public Image
{
public:
	PGMImage(const char* _path = "", const char* _magicNumber = "", unsigned int _rows = 0, unsigned int _cols = 0, unsigned int _colorMax = 0);
	PGMImage(const PGMImage& image);
	PGMImage& operator=(const PGMImage& image);
	~PGMImage();
public:
	Image* clone()
	{
		return new PGMImage(*this);
	}
	void load(std::istream& in) override;
	void save(std::ostream& out) override;
	void saveas(const char* direction) override;
	void collageHorizontal(std::ostream& out, int index) override;

	void Monochrome() override;
	void Negative() override;
	void Rotate(const char* direction) override;
private:
	unsigned short thresHold();
	void rotateRight();
	void copy(const PGMImage& image);
	void del();
private:
	int** pixels;
};
#endif // !__PGMIMAGE_HPP
