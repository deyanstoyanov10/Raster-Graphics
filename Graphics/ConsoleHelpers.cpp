#include "ConsoleHelpers.hpp"

ConsoleHelpers::ConsoleHelpers()
{
    this->inputService = new InputService();
}

ConsoleHelpers::~ConsoleHelpers()
{
    delete inputService;
}

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
    
    if (strcmp(commands[0], "load") == 0)
    {
        sessionStorage.AddSession(this->inputService->CreateNewSession(commands[1], sessionStorage.getIndex()));
        currentSessionId = sessionStorage.getIndex();
        std::cout << "Session with ID: " << sessionStorage.GetSessionId(sessionStorage.getIndex() - 1) << std::endl;
    }
    else if (strcmp(commands[0], "close") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->CheckForRemovingImage(sessionStorage, currentSessionId);
        
        this->inputService->RemoveImages(sessionStorage, currentSessionId);
        std::cout << "Successfully closed " << std::endl; //TODO: add file name
    }
    else if (strcmp(commands[0], "save") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->SaveFile(sessionStorage, currentSessionId);
    }
    else if (strcmp(commands[0], "saveas") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->SaveAsFile(sessionStorage, currentSessionId, commands[1]);
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
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->AddImages(sessionStorage, currentSessionId, commands[1]);
    }
    else if (strcmp(commands[0], "grayscale") == 0 || strcmp(commands[0], "monochrome") == 0 || strcmp(commands[0], "negative") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->ManipulateImages(sessionStorage, currentSessionId, commands[0]);
    }
    else if (strcmp(commands[0], "undo") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->Undo(sessionStorage, currentSessionId);
    }
    else if (strcmp(commands[0], "rotate") == 0 && (strcmp(commands[1], "left") == 0 || strcmp(commands[1], "right") == 0))
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->RotateImages(sessionStorage, currentSessionId, commands[1]);
    }
    else if (strcmp(commands[0], "collage") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->CollageMaker(sessionStorage, currentSessionId, commands[1], commands[2], commands[3], commands[4]);
    }
    else if (strcmp(commands[0], "session") == 0 && strcmp(commands[1], "info") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        this->inputService->SessionInfo(sessionStorage, currentSessionId);
    }
    else if (strcmp(commands[0], "switch") == 0)
    {
        this->inputService->CheckForAnySessions(sessionStorage);
        int newSessionId = commands[1][0] - '0';
        this->inputService->CheckForAnySessions(newSessionId);
        this->inputService->SwitchSession(currentSessionId, newSessionId);
        this->inputService->SessionInfo(sessionStorage, currentSessionId);
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