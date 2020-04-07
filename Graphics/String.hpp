#pragma once

#include<string.h>
#include<iostream>
#include<ostream>

#define BUFFER 1024

class String
{
public:
	String();
	String(char str);
	String(const char* str);
	String(const String& str);
	~String();

	String& operator=(const String& str);

	String& operator+= (char str);
	String& operator+= (const char* str);
	String& operator+= (const String& str);

	char operator[](unsigned index) const;
	char& operator[](unsigned index);

	friend String operator+(const String& strLeft, const String& strRight);
	friend String operator+(const String& strLeft, char strRight);
	friend String operator+(const String& strLeft, const char* strRight);
	friend String operator+(char strLeft, const String& strRight);
	friend String operator+(const char* strLeft, const String& strRight);

	friend bool operator==(const String& strLeft, const String& strRight);
	friend bool operator==(const String& strLeft, char strRight);
	friend bool operator==(const String& strLeft, const char* strRight);
	friend bool operator==(char strLeft, const String& strRight);
	friend bool operator==(const char* strLeft, const String& strRight);

	friend bool operator!=(const String& strLeft, const String& strRight);
	friend bool operator!=(const String& strLeft, char strRight);
	friend bool operator!=(const String& strLeft, const char* strRight);
	friend bool operator!=(char strLeft, const String& strRight);
	friend bool operator!=(const char* strLeft, const String& strRight);

	friend std::ostream& operator<< (std::ostream& out, const String& s);
	friend std::istream& operator>> (std::istream& in, const String& s);
public:
	unsigned int size() const { return length; }

private:
	void copy(const String& str);
	void del();
private:
	void setStr(const char* str);
	unsigned int length;
	char* string;
};