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

	Description: Game class renders eveything on screen and does the game logic
*/

#ifndef V2D_GAME_H
#define V2D_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Script.h"

#include "FPS.h"
class Game
{
public:
	void handleInput(sf::Event e);
	void render(sf::RenderWindow& window);
	void update();
	Game(std::vector<Statement>* _statements, int _width, int _height);
	void nextStatement();

private:
	sf::Music music;

	sf::Texture backgroundTex;
	sf::Sprite background;

	sf::RectangleShape fadeRect;
	int fade; // if it is fade out, then fade < 0, if fade in - fade > 0

	std::size_t ip; //Like instruction pointer
	std::vector<Statement>* statements;

	sf::RectangleShape textRect;

	sf::Text text;
	sf::Font textFont;

	sf::Clock textClock;
	sf::Clock delayClock;

	std::wstring textStr;
	bool hasPrintedText;
	std::string::size_type textPos;

	sf::Text debugText;
	FPS fpsCounter;

	int delay;
	int windowWidth;
	int windowHeight;

	bool hideText;
	bool fadeOn;

	bool debug;
};

#endif