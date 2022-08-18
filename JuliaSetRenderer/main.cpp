#define _SILENCE_AMP_DEPRECATION_WARNINGS 1
#include <iostream>
#include "Scene_app.h"
#include <fstream>
#include <vector>

int  main()
{
	bool init = true;

	int win_x;
	int win_y;

	std::vector<float> fps_storage;
	const float frame_rate = 60;
	const float average_smaples = 1000;

	std::ofstream outData;
	outData.open("output/runtime_data.csv");

	std::cout << "Window size X: ";
	std::cin >> win_x;
	std::cout << "Window size Y: ";
	std::cin >> win_y;

	sf::RenderWindow window(sf::VideoMode(win_x, win_y), "Title", sf::Style::None);

	sf::Event event;

	Scene_app scene(&window);

	StopWatch::Timer* timer = StopWatch::Timer::Instance();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			default:
				break;
			}
		}

		timer->Tick();

		if (timer->getDeltaTime() >= 1.f / frame_rate)
		{
			timer->Reset();

			if (init)
			{
				scene.init();
				init = false;
			}

			scene.update(timer->getDeltaTime());
			scene.render();

			if (fps_storage.size() < average_smaples)
			{
				fps_storage.push_back(1 / timer->getDeltaTime());
			}
		}
	}

	outData << "Raw FPS for the first " << fps_storage.size() << " frames." << std::endl;

	for (int i = 0; i < fps_storage.size(); i++)
	{
		if (i % (int)round(sqrt(fps_storage.size())) == 0)
		{
			outData << std::endl << fps_storage[i] << ",";
		}
		else
		{
			outData << fps_storage[i] << ",";
		}
	}

	timer->CleanUp();
	std::cin.get();
	return 0;
}