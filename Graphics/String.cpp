#pragma warning(disable: 4996)
#include "String.hpp"

String::String()
	:length(0)
{
	this->string = new char[1];
	strcpy(this->string, "");
}

String::String(char str)
	:length(1)
{
	this->string = new char[2];
	this->string[0] = str;
	this->string[1] = '\0';
}

String::String(const char* str)
	:length(strlen(str))
{
	setStr(str);
}

String::String(const String& str) : String()
{
	if (this != &str)
	{
		copy(str);
	}
}

String::~String()
{
	del();
}

void String::setStr(const char* str)
{
	if (str == nullptr)
	{
		this->string = new char[1];
		strcpy(this->string, "");
		return;
	}
	this->string = new char[strlen(str) + 1];
	strcpy(this->string, str);
}

void String::copy(const String& str)
{
	this->string = new char[strlen(str.string) + 1];
	strcpy(this->string, str.string);
	this->length = str.length;
}

void String::del()
{
	delete[] string;
}

String& String::operator=(const String& str)
{
	if (this != &str)
	{
		del();
		copy(str);
	}

	return *this;
}

// Operator +=

String& String::operator+=(char str)
{
	unsigned int newLength = length + 1;
	char* newStr = new char[newLength + 1];
	
	for (unsigned int i = 0; i < length; i++)
	{
		newStr[i] = string[i];
	}
	newStr[newLength - 1] = str;
	newStr[newLength] = '\0';

	delete[] string;
	this->length = newLength;
	this->string = newStr;

	return *this;
}

String& String::operator+=(const char* str)
{
	unsigned int newLength = length + strlen(str);
	char* newStr = new char[newLength + 1];

	for (unsigned int i = 0; i < length; i++)
	{
		newStr[i] = string[i];
	}

	for (unsigned int i = length; i < newLength; i++)
	{
		newStr[i] = str[i - length];
	}

	newStr[newLength] = '\0';

	delete[] string;
	this->length = newLength;
	this->string = newStr;

	return *this;
}

String& String::operator+=(const String& str)
{
	unsigned int newLength = length + str.length;
	char* newStr = new char[newLength + 1];

	for (unsigned int i = 0; i < length; i++)
	{
		newStr[i] = string[i];
	}

	for (unsigned int i = length; i < newLength; i++)
	{
		newStr[i] = str.string[i - length];
	}

	newStr[newLength] = '\0';

	delete[] string;
	this->length = newLength;
	this->string = newStr;

	return *this;
}

// End Operator +=
// Operator []

char String::operator[](unsigned index) const
{
	if (index >= length)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}

	return string[index];
}

char& String::operator[](unsigned index)
{
	if (index >= length)
	{
		throw std::out_of_range("Index was outside the bounds of the array.");
	}

	return string[index];
}

// End Operator []
// Operator +

String operator+(const String& strLeft, const String& strRight)
{
	return String(strLeft) += strRight; // fix
}

String operator+(const String& strLeft, char strRight)
{
	return String(strLeft) += strRight; // fix
}

String operator+(const String& strLeft, const char* strRight)
{
	return String(strLeft) += strRight; // fix
}

String operator+(char strLeft, const String& strRight)
{
	return String(strLeft) += strRight;
}

String operator+(const char* strLeft, const String& strRight)
{
	return String(strLeft) += strRight;
}

// End Operator +
// Operator ==

bool operator==(const String& strLeft, const String& strRight)
{
	if (strLeft.length != strRight.length)
	{
		return false;
	}

	int count = strLeft.length;
	int len = 0;
	while (len < count && (strLeft.string[len] == strRight.string[len]))
	{
		len++;
	}

	return count == len;
}

bool operator==(const String& strLeft, char strRight)
{
	return strLeft == String(strRight);
}

bool operator==(const String& strLeft, const char* strRight)
{
	return strLeft == String(strRight);
}

bool operator==(char strLeft, const String& strRight)
{
	return String(strLeft) == strRight;
}

bool operator==(const char* strLeft, const String& strRight)
{
	return String(strLeft) == strRight;
}

// End Operator ==
// Operator !=

bool operator!=(const String& strLeft, const String& strRight)
{
	return !(strLeft == strRight);
}

bool operator!=(const String& strLeft, char strRight)
{
	return !(strLeft == strRight);
}

bool operator!=(const String& strLeft, const char* strRight)
{
	return !(strLeft == strRight);
}

bool operator!=(char strLeft, const String& strRight)
{
	return !(strLeft == strRight);
}

bool operator!=(const char* strLeft, const String& strRight)
{
	return !(strLeft == strRight);
}

// End Operator !=

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.string;
	return out;
}

std::istream& operator>>(std::istream& in, const String& s)
{
	in.getline(s.string, BUFFER);
	return in;
}