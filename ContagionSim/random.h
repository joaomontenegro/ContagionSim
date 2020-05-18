#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cmath>

inline float Rand() {
	return float(rand()) / float(RAND_MAX);
}

inline float Rand(float max) {
	return max * Rand();
}

inline float Rand(float min, float max) {
	return min + Rand(max - min);
}

inline bool SampleProbability(float probability) {
	return Rand(1.0) < probability;
}

#endif // _RANDOM_H_
