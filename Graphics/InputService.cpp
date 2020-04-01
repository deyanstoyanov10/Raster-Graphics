#include "InputService.hpp"

bool InputService::CheckForAnySessions(SessionStorage sessionStorage)
{
	if (sessionStorage.getIndex() == 0)
	{
		return false;
	}

	return true;
}

bool InputService::CheckForRemovingImage(SessionStorage sessionStorage, int sessionId)
{
	int index = FindSessionIndexById(sessionStorage, sessionId);

	if (index == -1)
	{
		throw std::exception("Cannot find session index");
	}

	Session* sessions = sessionStorage.getSession();

	if (sessions[index].getSize() - 1 < 0)
	{
		return false;
	}
	
	return true;
}

int InputService::FindSessionIndexById(SessionStorage sessionStorage, int id)
{
	Session* sessions = sessionStorage.getSession();
	for (int i = 0; i < sessionStorage.getIndex(); i++)
	{
		if (sessions[i].getSessionId() == id)
		{
			return i;
		}
	}

	return -1;
}

void InputService::SaveFile(Session session)
{
	Image** images = session.getImages();

	for (int i = 0; i < session.getSize(); i++)
	{
		std::fstream fout(images[i]->getPath(), std::ios::out);

		if (!fout.is_open())
		{
			throw new std::exception("Cannot open file");
		}
		images[i]->save(fout);

		fout.close();
	}
}

Session InputService::CreateNewSession(const char* filePath, int sessionId)
{
	if (filePath == nullptr)
	{
		throw std::exception("Something is wrong with path value");
	}

	Session session = Session(sessionId + 1);
	Image* image = CreateImage(filePath);
	session.AddImage(image);
	return session;
}

Image* InputService::CreateImage(const char* filePath)
{
	std::fstream fin(filePath, std::ios::in);

	if (!fin.is_open())
	{
		throw std::exception("Cannot open file!");
	}

	char magicString[10];
	unsigned int cols, rows, colorMax;

	fin >> magicString;

	if (strcmp(magicString, "P1") != 0 && strcmp(magicString, "P2") != 0 && strcmp(magicString, "P3") != 0)
	{
		throw std::exception("Incorrect file format");
	}

	fin >> cols >> rows >> colorMax;

	if (strcmp(magicString, "P1") == 0)
	{
		Image* image = new PBMImage(filePath, magicString, rows, cols, colorMax);
		image->load(fin);

		return image;
	}
	else if (strcmp(magicString, "P2") == 0)
	{
		Image* image = new PGMImage(filePath, magicString, rows, cols, colorMax);
		image->load(fin);

		return image;
	}
	else if (strcmp(magicString, "P3") == 0)
	{
		Image* image = new PPMImage(filePath, magicString, rows, cols, colorMax);
		image->load(fin);

		return image;
	}
	else
	{
		throw std::exception("Cannot read file");
	}
}