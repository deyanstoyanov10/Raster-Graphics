#ifndef __SESSION_HPP
#define __SESSION_HPP

#include <string.h>
#include "Image.hpp"

#define MAX_CAPACITY 10
#define MAX_PATH_LENGTH 30

class Session
{
public:
	Session(unsigned int _sessionId = 1, unsigned int _capacity = MAX_CAPACITY);
	Session(const Session& session);
	Session& operator=(const Session& session);
	~Session();

	int getSessionId() const { return this->sessionId; }
	int getSize() const { return this->size; }
	Image** getImages() const { return this->images; }
public:
	void AddImage(Image* image);
	void RemoveImage();
	void ManipulateImages(const char* command);
	void SessionInfo();
private:
	void copy(const Session& session);
	void del();
	
	void resize(unsigned int newCapacity);
private:
	unsigned int sessionId;
	unsigned int capacity;
	unsigned int size;
	Image** images;
};
#endif // !__SESSION_HPP
