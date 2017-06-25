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

	Description: This class parses script.vanilla2d file and turns it into vector<Statement>
*/

#include "Script.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#include "Logger.h"
#include "Utils.h"

bool Script::open(std::string filename) {
	m_file.open(filename);
	return m_file.good();
}

std::vector<Statement> Script::parse()
{
	//Thanks to nmcf for next line! (http://www.cyberforum.ru/members/469738.html)
	m_file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));

	std::vector<Statement> v;

	std::wstring stStr;
	sf::Clock clock;
	int line = 0;

	//Read file line by line
	while (std::getline(m_file, stStr))
	{
		std::wstring type;
		Statement s;
		line++;

		//We do NOT use something like split(), because we need only first token to determine statement type and consider another part of	    string as content
		for (int i=0;i<stStr.size();i++) {
			if (stStr[i] == L' ') {
				type = stStr.substr(0, i);

				if (type == L"txt") {
					s.wtext = stStr.substr(i+1);
				} else {
					char mbstr[255];
					std::wcstombs(mbstr, stStr.substr(i+1).c_str(), 255);
					std::string cstr(mbstr);
					s.content = cstr;
				}
				break;
			}
		}
		

		//Determine statement type
		//Sorry, for this IF tree
		if (type == L"music") {
			s.type = StatementType::MUSIC;
		} else if (type == L"bg") {
			s.type = StatementType::BACKGROUND;
		} else if (type == L"delay") {
			s.type = StatementType::DELAY;
		} else if (type == L"txt") {
			s.type = StatementType::TEXT;
		} else if (type == L"font") {
			s.type = StatementType::FONT;
		} else if (type == L"text_color") {
			s.type = StatementType::TEXT_COLOR;
		} else if (type == L"fade") {
			s.type = StatementType::FADE;
		} else {
			LOGGER->Log("Script", "WARNING: unknown script token at line %d", line);
			continue;
		}

		//Push the statement into vector
		v.push_back(s);
	}


	LOGGER->Log("Script", "Finished parsing %d lines in %d ms", line+1, clock.getElapsedTime().asMilliseconds());

	//Return vector to engine.
	return v;
}
