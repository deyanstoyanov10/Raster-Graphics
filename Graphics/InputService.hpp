#ifndef __INPUTSERVICE_HPP
#define __INPUTSERVICE_HPP

#include <fstream>

#include "Image.hpp"
#include "PBMImage.hpp"
#include "PGMImage.hpp"
#include "PPMImage.hpp"
#include "SessionStorage.hpp"

class InputService
{
public:
	void CheckForAnySessions(SessionStorage sessionStorage);
	void CheckForRemovingImage(SessionStorage sessionStorage, int sessionId);

	Session CreateNewSession(const char* filePath, int sessionId);
	void SwitchSession(int& sessionId, int newSessionId);

	void SaveFile(SessionStorage& sessionStorage, int sessionId);
	void SaveAsFile(SessionStorage& sessionStorage, int sessionId, const char* path);
private:
	int FindSessionIndexById(SessionStorage& sessionStorage, int id);
	Session& GetSessionById(SessionStorage& sessionStorage, int sessionId);
	Image* CreateImage(const char* filePath);
public:
	void SessionInfo(SessionStorage& sessionStorage, int sessionId);
	void AddImages(SessionStorage& sessionStorage, int sessionId, const char* image);
	void RemoveImages(SessionStorage& sessionStorage, int sessionId);
	void Undo(SessionStorage& sessionStorage, int sessionId);
	void ManipulateImages(SessionStorage& sessionStorage, int sessionId, const char* command);
	void RotateImages(SessionStorage& sessionStorage, int sessionId, const char* direction);
	void CollageMaker(SessionStorage& sessionStorage, int sessionId, const char* direction, const char* firstImage, const char* secondImage, const char* outImage);
};
#endif // !__INPUTSERVICE_HPP
