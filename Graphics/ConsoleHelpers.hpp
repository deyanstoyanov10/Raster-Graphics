#ifndef __CONSOLEHELPERS_HPP
#define __CONSOLEHELPERS_HPP

#include <iostream>
#include "InputService.hpp"

#define BUFFER 100

class ConsoleHelpers
{
public:
	ConsoleHelpers();
	~ConsoleHelpers();

	void ReadCommands(SessionStorage& sessionStorage, int& currentSessionId);
	void RenderConsole();
private:
	void RenderHelp();
private:
	void InitializeCommand(const char* input, int& currentSessionId, SessionStorage& sessionStorage);
	void ExtractWords(const char* input, char**& commands);
	int WordCount(const char* text);
	bool IsWordLetter(char c);
private:
	InputService* inputService;
};
#endif // !__CONSOLEHELPERS_HPP
