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

	Description: Logger class logs given formatted string into Vanilla2DEngine.log
*/

#ifndef V2D_LOGGER_H
#define V2D_LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

#ifdef __linux__
int _vscprintf (const char * format, va_list pargs); 
#endif

#define LOGGER Logger::GetLogger()
class Logger
{
public:
    void Log(const std::string& tag, std::string& sMessage);
    void Log(const std::string& tag, const char * format, ...);

   Logger& operator<<(const string& sMessage);

    static Logger* GetLogger();
private:
    Logger();

    static const std::string m_sFileName;

    static Logger* m_pThis;

    static ofstream m_Logfile;

	static sf::Clock m_clock;
};
#endif
