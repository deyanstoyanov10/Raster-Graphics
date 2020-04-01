#include "Engine.hpp"

void Engine::Run()
{
	ConsoleHelpers console;
	console.RenderConsole();

	SessionStorage sessionStorage = SessionStorage();
	int currentSessionId = 0;

	while (true)
	{
		try
		{
			console.ReadCommands(sessionStorage, currentSessionId);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
