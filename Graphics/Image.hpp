#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include <istream>
#include <string.h>
#include <iostream>
#include <fstream>

class Image
{
public:
	Image(const char* _path = "", const char* _magicNumber = "", unsigned int _rows = 0, unsigned int _cols = 0, unsigned int _colorMax = 0);
	virtual ~Image();
public:
	virtual Image* clone();
	const char* getPath() const { return this->path; }
	const char* getMagicNumber() const { return this->magicNumber; }
	const int getColorMax() const { return this->colorMax; }
	const int getRows() const { return this->rows; }
	const int getCols() const { return this->cols; }
	char* getFileName() const;
	void PrintFileName();

	virtual void load(std::istream& in) = 0;
	virtual void save(std::ostream& out) = 0;
	virtual void saveas(const char* direction) = 0;
	virtual void collageHorizontal(std::ostream& out, int index) = 0;

	virtual void GrayScale();
	virtual void Monochrome();
	virtual void Negative();
	virtual void Rotate(const char* direction);
private:
	void copy(const Image& image);
	void del();
protected:
	void setPath(const char* path);
	void setMagicNumber(const char* magicNumber);

	char* path;
	char* magicNumber;
	unsigned int rows;
	unsigned int cols;
	unsigned int colorMax;
};
#endif // !__IMAGE_HPP
