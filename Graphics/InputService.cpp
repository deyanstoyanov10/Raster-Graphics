#include "InputService.hpp"

void InputService::CheckForAnySessions(SessionStorage sessionStorage)
{
	if (sessionStorage.getIndex() == 0)
	{
		throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
	}
}

void InputService::CheckForRemovingImage(SessionStorage sessionStorage, int sessionId)
{
	int index = FindSessionIndexById(sessionStorage, sessionId);

	if (index == -1)
	{
		throw std::exception("Cannot find session index");
	}

	Session* sessions = sessionStorage.getSession();

	if (sessions[index].getSize() - 1 < 0)
	{
		throw std::exception("You can't remove images from that session");
	}
}

int InputService::FindSessionIndexById(SessionStorage& sessionStorage, int id)
{
	Session* sessions = sessionStorage.getSession();

	int result = -1;

	for (int i = 0; i < sessionStorage.getIndex(); i++)
	{
		if (sessions[i].getSessionId() == id)
		{
			result = i;
			break;
		}
	}

	if (result == -1)
	{
		throw std::exception("Invalid session Id");
	}

	return result;
}

Session& InputService::GetSessionById(SessionStorage& sessionStorage, int sessionId)
{
	int index = FindSessionIndexById(sessionStorage, sessionId);
	Session* sessions = sessionStorage.getSession();
	return sessions[index];
}

void InputService::SaveFile(SessionStorage& sessionStorage, int sessionId)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	Image** images = session.getImages();

	for (int i = 0; i < session.getSize(); i++)
	{
		std::fstream fout(images[i]->getPath(), std::ios::out);

		const char* magicNumber = images[i]->getMagicNumber();
		fout << magicNumber << std::endl;
		fout << images[i]->getCols() << " " << images[i]->getRows() << std::endl;
		fout << images[i]->getColorMax() << std::endl;

		if (!fout.is_open())
		{
			throw new std::exception("Cannot open file");
		}
		images[i]->save(fout);

		fout.close();
	}
}

void InputService::SaveAsFile(SessionStorage& sessionStorage, int sessionId, const char* path)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	Image** images = session.getImages();

	for (int i = 0; i < session.getSize(); i++)
	{
		images[i]->saveas(path);
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

void InputService::SwitchSession(int& sessionId, int newSessionId)
{
	sessionId = newSessionId;
	std::cout << "You switched to session with ID : " << sessionId << "!" << std::endl;
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

void InputService::SessionInfo(SessionStorage& sessionStorage, int sessionId)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.SessionInfo();
}

void InputService::AddImages(SessionStorage& sessionStorage, int sessionId, const char* image)
{
	Image* img = CreateImage(image);
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.AddImage(img);
}

void InputService::RemoveImages(SessionStorage& sessionStorage, int sessionId)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.RemoveImage();
}

void InputService::Undo(SessionStorage& sessionStorage, int sessionId)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.UndoLastChanges();
}

void InputService::ManipulateImages(SessionStorage& sessionStorage, int sessionId, const char* command)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.ManipulateImages(command);
}

void InputService::RotateImages(SessionStorage& sessionStorage, int sessionId, const char* direction)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.RotateImages(direction);
}

void InputService::CollageMaker(SessionStorage& sessionStorage, int sessionId, const char* direction, const char* firstImage, const char* secondImage, const char* outImage)
{
	Session& session = GetSessionById(sessionStorage, sessionId);
	session.MakeCollage(direction, firstImage, secondImage, outImage);
}
