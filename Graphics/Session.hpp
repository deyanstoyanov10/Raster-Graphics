#ifndef __SESSION_HPP
#define __SESSION_HPP

#include <string.h>
#include "Image.hpp"
#include "History.hpp"

#define MAX_CAPACITY 10
#define MAX_PATH_LENGTH 30
#define HISTORY_CAPACITY 10

class Session
{
public:
	Session(unsigned int _sessionId = 1, unsigned int _capacity = MAX_CAPACITY, unsigned int _historyCapacity = HISTORY_CAPACITY);
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
	void UndoLastChanges();
private:
	void addToHistory(const char* beforeChanges);
	void copy(const Session& session);
	void del();
	
	void resize(unsigned int newCapacity);
	void resizeHistory(unsigned int newHistoryCapacity);
private:
	unsigned int sessionId;
	unsigned int capacity;
	unsigned int size;
	Image** images;

	unsigned int historyCapacity;
	unsigned int historySize;
	History* history;
};
#endif // !__SESSION_HPP
