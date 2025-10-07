#pragma once
#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H
#include <deque>
#include <numeric>
class FPSCounter {
private:
	std::deque<float> frameAverages;
	std::deque<float> singleFrameAverage;
public:
	FPSCounter();
	void addFrame(float fps);
	float getAverageFPS() const;
	float update(float frametime);
};
#endif