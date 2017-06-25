/*
	Original code by BarrensZeppelin: https://github.com/SFML/SFML/wiki/Source:-FPS
*/


#include <SFML/Graphics.hpp>

#ifndef FPS_H
#define FPS_H

class FPS
{ 
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}

	/// @brief Update the frame count.
	/// 
	void update();

	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;
};


#endif // FPS_H