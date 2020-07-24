#include "disease.h"
#include "random.h"

Disease::Disease(float transmissionRate)
	: _transmissionRate(transmissionRate)
{
	if (_transmissionRate > 1.0f) {
		_transmissionRate = 1.0f;
	}
}

Disease::~Disease() {}
