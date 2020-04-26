#pragma warning(disable: 4996)
#include "String.hpp"

String::String()
	:length(0)
{
	this->string = new char[1];
	strcpy(this->string, "");
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

void String::serialize(std::ofstream& ofs)
{
	if (!ofs.is_open())
	{
		throw std::exception("Problem has occured.");
	}

	unsigned int length = strlen(string);
	ofs.write((const char*)&length, sizeof(length));
	ofs.write(string, length * sizeof(char));
}

void String::deserialize(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		throw std::exception("Problem has occured.");
	}

	unsigned int length = 0;
	ifs.read((char*)&length, sizeof(length));
	char* str = new char[length + 1];
	ifs.read(str, length);
	str[length] = '\0';


	delete[] string;
	string = str;
	this->length = length;
}

Vector<String> String::strSplit(char splitter, const char* str)
{
	Vector<String> words;

	int count = wordsCount(splitter, str);
	for (int i = 0; i < count; i++) {

		while (*str && !isCharLetter(splitter, *str))
			++str;
		if (*str) {
			const char* start = str;
			while (isCharLetter(splitter, *str))
				++str;

			int len = str - start;
			char* s = new char[len + 1];

			for (int pos = 0; pos < len; ++pos)
				s[pos] = start[pos];
			s[len] = '\0';

			String word = s;
			words.push_back(word);
			delete[] s;
		}
	}

	return words;
}

bool String::contains(char c)
{
	bool contains = false;

	for (unsigned int i = 0; i < length; i++)
	{
		if (string[i] == c)
		{
			contains = true;
			break;
		}
	}

	return contains;
}

int String::parseToInt()
{
	int number = std::atoi(string);
	return number;
}

float String::parseToFloat()
{
	float temp = ::atof(string);
	return temp;
}

void String::repeat(const String& str, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
	{
		std::cout << str;
	}
	//std::cout << std::endl;
}

int String::wordsCount(char splitter, const char* str)
{
	int count = 0;
	while (*str) {
		while (*str && !isCharLetter(splitter, *str)) {
			++str;
		}
		if (*str) {
			++count;
		}
		while (isCharLetter(splitter, *str)) {
			++str;
		}
	}

	return count;
}

bool String::isCharLetter(char splitter, char c)
{
	if (c == splitter)
	{
		return false;
	}

	if (c != '\0')
	{
		return true;
	}

	return false;
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

String operator+(const String& strLeft, const char* strRight)
{
	return String(strLeft) += strRight; // fix
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

bool operator==(const String& strLeft, const char* strRight)
{
	return strLeft == String(strRight);
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

bool operator!=(const String& strLeft, const char* strRight)
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

std::istream& operator>>(std::istream& in, String& s)
{
	char input[BUFFER];
	in.getline(input, BUFFER);

	String inp = input;
	s = inp;

	return in;
}