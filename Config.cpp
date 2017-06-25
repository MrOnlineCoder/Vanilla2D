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

	Description: Class, that parses configuration file
*/

#include "Config.h"
#include "Logger.h"
#include "ConfigParser.h"

#include <string>


// Default config options
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int FPS = 30;
const std::string TITLE = "Vanilla2D Application";

ConfigOptions Config::parse(std::string filename) {
	//Fill the struct with defaults
	ConfigOptions opts;
	opts.width = WINDOW_WIDTH;
	opts.height = WINDOW_HEIGHT;
	opts.fps = FPS;
	opts.title = TITLE;

	ConfigParser settings;
    if(!settings.loadFromFile(filename))
    {
        LOGGER->Log("ConfigParser", "ERROR: failed to open application config! Defaults are applied");
        return opts;
    }

    settings.get("width", opts.width);

    settings.get("height", opts.height);

    settings.get("title", opts.title);

	settings.get("fps", opts.fps);

	return opts;
}