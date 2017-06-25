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

#include "Game.h"
#include "Script.h"
#include "Logger.h"
#include "Utils.h"

#include <locale>
#include <string>
#include <sstream>
#include <codecvt>


Game::Game(std::vector<Statement>* _statements, int _width, int _height) {

	//Reset class memebers to default
	statements = _statements;
	ip = -1;
	windowWidth = _height;
	windowWidth = _width;
	hasPrintedText = false;
	textPos = 0;
	hideText = false;
	delay = 0;
	fade = 0;
	fadeOn = false;
	debug = false;

	//Setup text rect
	textRect.setPosition(sf::Vector2f(16.f, (float) _height-16-128));
	textRect.setSize(sf::Vector2f((float) _width-32.f, 128.f));
	textRect.setFillColor(sf::Color(0,0,0,75)); //75!!
	textRect.setOutlineThickness(2);
	textRect.setOutlineColor(sf::Color(0,0,0,255));

	fadeRect.setSize(sf::Vector2f(_width, _height));
	fadeRect.setPosition(sf::Vector2f(0,0));
	fadeRect.setFillColor(sf::Color::Black);


	//Load default font
	if (!textFont.loadFromFile("game/fonts/script.ttf")) {
		LOGGER->Log("Game","ERROR: Failed to load font game/fonts/script.ttf");
	} else {
		text.setFont(textFont);
		text.setFillColor(sf::Color::Black);
		text.setPosition(textRect.getPosition()+sf::Vector2f(7,5));
		text.setCharacterSize(24);
		debugText.setFont(textFont);
	}

	debugText.setPosition(sf::Vector2f(5,5));
	debugText.setFillColor(sf::Color::Black);
	debugText.setCharacterSize(18);
	


	//Start executing statements
	nextStatement();
}

void Game::handleInput(sf::Event e) {

	//Show next text on mouse click
	if (e.type == sf::Event::MouseButtonReleased && delay == 0 && !fadeOn) {
		nextStatement();
	}

	if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::F3) {
		debug = !debug;
	}
}

void Game::nextStatement() {
	//Stop if EOV (end-of-vector)
	if (ip+1 == statements->size()) return;

	//Increment instruction pointer
	ip++;

	//Execute current statement
	Statement s = statements->at(ip);
	if (s.type == StatementType::BACKGROUND) {
		std::string path = "game/img/" + s.content;
		if (!backgroundTex.loadFromFile(path)) {
			LOGGER->Log("Game","ERROR: Failed to load background %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed background to %s", s.content.c_str());
		}
		background.setTexture(backgroundTex);
		background.setPosition(sf::Vector2f(0,0));

		nextStatement();
		return;
	}

	if (s.type == StatementType::TEXT) {
		textStr = s.wtext;
		text.setString(textStr[0]);
		hasPrintedText = false;
		textPos = 0;
		return;
	}

	if (s.type == StatementType::DELAY) {
		delay = atoi(s.content.c_str());
		hideText = true;
		delayClock.restart();
	}

	if (s.type == StatementType::FONT) {
		if (!textFont.loadFromFile("game/fonts/"+s.content)) {
			LOGGER->Log("Game","ERROR: Failed to load background %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed font to %s", s.content.c_str());
		}
		nextStatement();
	}

	if (s.type == StatementType::TEXT_COLOR) {
		sf::Color c = Utils::parseColor(s.content);
		text.setFillColor(c);
		LOGGER->Log("Game","Changed text color to RGBA(%d,%d,%d,%d)", c.r, c.g, c.b, c.a);
		nextStatement();
	}

	if (s.type == StatementType::MUSIC) {
		std::string path = "game/music/" + s.content;
		if (!music.openFromFile(path)) {
			LOGGER->Log("Game","ERROR: Failed to load music %s at statement %d", s.content.c_str(), ip);
		} else {
			LOGGER->Log("Game","Changed music to %s", s.content.c_str());
		}
		music.setLoop(true);
		music.play();

		nextStatement();
		return;
	}

	if (s.type == StatementType::FADE) {
		std::stringstream ss(s.content);
		int n = 0;
		std::string way;

		ss >> way; //in or out
		ss >> n; //fade speed

		if (way == "in") {
			fade = n;
			fadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,0));
			hideText = true;
		} else if (way == "out"){
			fade = -n;
			fadeOn = true;
			fadeRect.setFillColor(sf::Color(0,0,0,255));
			hideText = true;
		} else {
			LOGGER->Log("Game", "Unknown fade value at statements %d. Only 'in' and 'out' values are supported.", ip);
		}
	}
}

void Game::update() {

	//Text printing animation
	if (!hasPrintedText && textClock.getElapsedTime().asMilliseconds() > 30) {
		textPos++;
		if (textPos >= textStr.size()) {
			hasPrintedText = false;
		} else {
			std::wstring newStr = text.getString().toWideString();
			newStr += textStr[textPos];
			sf::String newsfStr(newStr);
			sf::String wrappedStr = Utils::wrapText(newsfStr, static_cast<unsigned int>(textRect.getSize().x), textFont, 24.f);
			text.setString(wrappedStr);
		}

	}

	//Delay logic
	if (delay > 0 && delayClock.getElapsedTime().asMilliseconds() > delay) {
		hideText = false;
		delay = 0;
		nextStatement();
	}

	if (fadeOn) {
		sf::Color c = fadeRect.getFillColor();

		//Change fadeRect alpha


		//If fade animation is finished, continue executing statements
		if (fade < 0 && fade + c.a < 0) {
			fadeOn = false;
			hideText = false;
			nextStatement();
			return;
		} else if (fade > 0 && fade + c.a > 255) {
			fade = 0; // We do not set fadeOn to false to allow executing next statements without losing fade rect state
			hideText = false;
			nextStatement();
			return;
		} else {
			//If animation is in process, set rect color
			c.a += fade;
			fadeRect.setFillColor(c);
		}
	}

	if (debug) {
		std::stringstream ss;
		ss << "FPS: " << fpsCounter.getFPS() << "\n" << "statement:" << ip;
		debugText.setString(ss.str());
	}
}

void Game::render(sf::RenderWindow& window) {
	window.draw(background);

	if (fadeOn) window.draw(fadeRect);

	//Draw only if text is not hidden
	if (!hideText) {
		window.draw(textRect);
		window.draw(text);
	}

	if (debug) window.draw(debugText);

	fpsCounter.update();
}