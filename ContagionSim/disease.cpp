#include "disease.h"
#include "random.h"

Disease::Disease(float rate)
	: _rate(rate)
{
	if (_rate > 1.0f) {
		_rate = 1.0f;
	}
}

Disease::~Disease() {}
