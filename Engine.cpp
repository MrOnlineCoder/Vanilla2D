/*

	MIT License

	Copyright (c) 2017 Nikita Kogut (MrOnlineCoder)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Description: Engine class loads all settings, creates window and eneters window event loop
*/

#include "Engine.h"
#include "Logger.h"
#include "Script.h"
#include "Config.h"

#include <fstream>
#include <sstream>

int Engine::start()
{
	//Load game name, window's size and fps limit from app.vanilla2d
	LOGGER->Log("Engine","Loading game info...");
	/*std::ifstream appFile("game/app.vanilla2d"); 

	//Error check
	if (!appFile.good()) {
		LOGGER->Log("Engine","ERROR: app.vanilla2d file cannot be opened!");
		return 1;
	}

	std::string appName;
	int windowWidth = 640;
	int windowHeight = 480;
	int fpsLimit = 30;

	std::getline(appFile, appName);
	appFile >> windowWidth;
	appFile >> windowHeight;
	appFile >> fpsLimit;*/

	ConfigOptions opts;
	Config cfg;
	opts = cfg.parse("game/app.vanilla2d");

	LOGGER->Log("Engine","App Name: %s",opts.title.c_str());
	LOGGER->Log("Engine","Window Size: %d x %d", opts.width, opts.height);
	LOGGER->Log("Engine","FPS Limit: %d", opts.fps);


	//Parse game script
	LOGGER->Log("Engine","Parsing game script...");
	Script script;

	//Error check
	if (!script.open("game/script.vanilla2d")) {
		LOGGER->Log("Engine","ERROR: script file cannot be opened!");
		return 1;
	}

	statements = script.parse();
	LOGGER->Log("Engine","Loaded %d statements", statements.size());

	//Create the window and enter the loop
	LOGGER->Log("Engine","Creating window...");
	window.create(sf::VideoMode(opts.width, opts.height), opts.title+" (Powered by Vanilla2D)");
	window.setFramerateLimit(opts.fps);

	LOGGER->Log("Engine","Creating Game instance...");
	Game game(&statements, opts.width, opts.height);


	LOGGER->Log("Engine","Enetring window event loop...");
	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {

			//If Close button is clicked, exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//Let game handle all other events
			game.handleInput(event);
		}

		//Update game logic, animations
		game.update();


		//Render everything
		window.clear();
		game.render(window);
		window.display();
	}

	LOGGER->Log("Engine","Window has been closed, exiting...");
	LOGGER->Log("Engine","ENGINE SHUTDOWN");

	return 0;
}
