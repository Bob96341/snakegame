#include "fpscounter.h"
void FPSCounter::addFrame(float fps) {
	if (singleFrameAverage.size() < 5)
		singleFrameAverage.push_back(fps);
	else {
		frameAverages.push_back(std::accumulate(singleFrameAverage.begin(), singleFrameAverage.end(), 0.f) / singleFrameAverage.size());
		singleFrameAverage.clear();
		singleFrameAverage.push_back(fps);
		if (frameAverages.size() > 10)
			frameAverages.pop_front();
	}
}
float FPSCounter::getAverageFPS() const {
	if (frameAverages.empty()) return 0.f;
	return std::accumulate(frameAverages.begin(), frameAverages.end(), 0.f) / frameAverages.size();
}
float FPSCounter::update(float frametime) {
	addFrame(1.f / frametime);
	return getAverageFPS();
}
FPSCounter::FPSCounter() : frameAverages(), singleFrameAverage() {}