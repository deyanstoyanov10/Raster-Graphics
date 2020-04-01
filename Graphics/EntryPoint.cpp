#include "Engine.hpp"

int main()
{
	Engine engine = Engine();
	engine.Run();

	/*Session sessionOne = Session();

	Image* firstImage = new PPMImage();
	Image* secondImage = new PPMImage();

	sessionOne.AddImage(firstImage);
	sessionOne.AddImage(secondImage);

	Session secondSession = sessionOne;

	for (int i = 0; i < 2; i++)
	{
		Image** imgs = sessionOne.getImages();
		std::cout << imgs[i] << std::endl;

		Image** imgsTwo = secondSession.getImages();
		std::cout << imgsTwo[i] << std::endl;
	}*/
	return 0;
}