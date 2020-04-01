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
	bool CheckForAnySessions(SessionStorage sessionStorage);
	bool CheckForRemovingImage(SessionStorage sessionStorage, int sessionId);
	int FindSessionIndexById(SessionStorage sessionStorage, int id);

	void SaveFile(Session session);
	Session CreateNewSession(const char* filePath, int sessionId);
	Image* CreateImage(const char* filePath);
};
#endif // !__INPUTSERVICE_HPP
