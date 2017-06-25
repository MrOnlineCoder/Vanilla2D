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

*/

#include "Logger.h"
#include "Utils.h"
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

sf::String Utils::wrapText(sf::String string, unsigned width, const sf::Font &font, unsigned charicterSize, bool bold){
  unsigned currentOffset = 0;
  bool firstWord = true;
  std::size_t wordBegining = 0;

  for (std::size_t pos(0); pos < string.getSize(); ++pos) {
    auto currentChar = string[pos];
    if (currentChar == '\n'){
      currentOffset = 0;
      firstWord = true;
      continue;
    } else if (currentChar == ' ') {
      wordBegining = pos;
      firstWord = false;
    }

    auto glyph = font.getGlyph(currentChar, charicterSize, bold);
    currentOffset += glyph.advance;

    if (!firstWord && currentOffset > width) {
      pos = wordBegining;
      string[pos] = '\n';
      firstWord = true;
      currentOffset = 0;
    }
  }

  return string;
}


sf::Color Utils::parseColor(std::string str) {
	std::istringstream ss(str);

	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	ss >> r;
	ss >> g;
	ss >> b;
	ss >> a;

	sf::Color newColor(r,g,b,a);
	return newColor;
}