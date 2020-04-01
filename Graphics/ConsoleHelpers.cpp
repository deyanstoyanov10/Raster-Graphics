#include "ConsoleHelpers.hpp"

void ConsoleHelpers::ReadCommands(SessionStorage& sessionStorage, int& currentSessionId)
{
	char input[BUFFER];
	std::cin.getline(input, BUFFER);
    InitializeCommand(input, currentSessionId, sessionStorage);
}

void ConsoleHelpers::RenderConsole()
{
	std::cout << "//===== Welcome to Raster Graphics =====//" << std::endl;
	std::cout << "Type help for more information" << std::endl;
}

void ConsoleHelpers::RenderHelp()
{
	std::cout << "//===== Information =====//" << std::endl;
	std::cout << "The following commands are supported:" << std::endl;
	std::cout << "open <file_path>	opens <file>" << std::endl;
	std::cout << "close	=> closes currently opened file" << std::endl;
	std::cout << "save => saves the currently open file" << std::endl;
	std::cout << "saveas <file>	saves the currently open file in <file>" << std::endl;
	std::cout << "help => prints this information" << std::endl;
	std::cout << "exit => exists the program" << std::endl;
}

void ConsoleHelpers::InitializeCommand(const char* input, int& currentSessionId, SessionStorage& sessionStorage)
{
    char** commands;
    ExtractWords(input, commands);
    
    InputService inputService = InputService();
    
    if (strcmp(commands[0], "load") == 0)
    {
        sessionStorage.AddSession(inputService.CreateNewSession(commands[1], sessionStorage.getIndex()));
        currentSessionId = sessionStorage.getIndex();
        std::cout << "Session with ID: " << sessionStorage.GetSessionId(sessionStorage.getIndex() - 1) << std::endl;
    }
    else if (strcmp(commands[0], "close") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        else if (!inputService.CheckForRemovingImage(sessionStorage, currentSessionId))
        {
            throw std::exception("You can't remove images from that session");
        }
        
        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();
        sessions[index].RemoveImage();

        std::cout << "Successfully closed " << std::endl; //TODO: add file name
    }
    else if (strcmp(commands[0], "save") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();

        inputService.SaveFile(sessions[index]);
    }
    else if (strcmp(commands[0], "saveas") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
    }
    else if (strcmp(commands[0], "help") == 0)
    {
        RenderHelp();
    }
    else if (strcmp(commands[0], "exit") == 0)
    {
        std::cout << "Exiting the program..." << std::endl;
        exit(0);
    }
    else if (strcmp(commands[0], "add") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        Image* image = inputService.CreateImage(commands[1]);

        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();
        sessions[index].AddImage(image);
    }
    else if (strcmp(commands[0], "grayscale") == 0 || strcmp(commands[0], "monochrome") == 0 || strcmp(commands[0], "negative") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }

        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();
        sessions[index].ManipulateImages(commands[0]);
    }
    else if (strcmp(commands[0], "undo") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        
        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();
        sessions[index].UndoLastChanges();
    }
    else if (strcmp(commands[0], "session") == 0 && strcmp(commands[1], "info") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        int index = inputService.FindSessionIndexById(sessionStorage, currentSessionId);
        Session* sessions = sessionStorage.getSession();
        sessions[index].SessionInfo();
    }
    else if (strcmp(commands[0], "switch") == 0)
    {
        if (!inputService.CheckForAnySessions(sessionStorage))
        {
            throw std::exception("You dont have sessions yet. Create session with open/load <file_path>");
        }
        int sessionId = commands[1][0] - '0';
        int index = inputService.FindSessionIndexById(sessionStorage, sessionId);
        
        if (index == - 1)
        {
            throw std::exception("Invalid session Id");
        }

        currentSessionId = sessionId;
        std::cout << "You switched to session with ID : " << currentSessionId << "!" << std::endl;
        Session* sessions = sessionStorage.getSession();
        sessions[index].SessionInfo();
    }
    else
    {
        throw std::exception("Wrong function. Type help for more information");
    }
}

void ConsoleHelpers::ExtractWords(const char* input, char **& commands)
{
    int count = WordCount(input);
    commands = new char* [count];
    
    for (unsigned int i = 0; i < count; i++) {

        while (*input && !IsWordLetter(*input))
            ++input;
        if (*input) {
            const char* start = input;
            while (IsWordLetter(*input))
                ++input;
    
            int len = input - start;
            commands[i] = new char[len + 1];
            
            for (int pos = 0; pos < len; ++pos)
                commands[i][pos] = start[pos];
            commands[i][len] = '\0';
        }
    }
}

int ConsoleHelpers::WordCount(const char* text)
{
    int cnt = 0;
    while (*text) {
        while (*text && !IsWordLetter(*text)) {
            ++text;
        }
        if (*text) {
            ++cnt;
        }
        while (IsWordLetter(*text)) {
            ++text;
        }
    }
    return cnt;
}

bool ConsoleHelpers::IsWordLetter(char c)
{
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_' || c == '.' ||
        c == '/' || c == '\\';
}