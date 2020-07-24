#include "disease.h"
#include "random.h"

Disease::Disease(float transmissionRate, int numInitialInfected)
	: _transmissionRate(transmissionRate)
	, _numInitialInfected(numInitialInfected)
{
	if (_transmissionRate > 1.0f) {
		_transmissionRate = 1.0f;
	}
}

Disease::~Disease() {}

void
Disease::init() {
	// Initially infected
	for (size_t i = 0; i < _simulation->getNumAgents(); ++i) {
		if (i < _numInitialInfected) {
			_simulation->getAgent(i).infect();
		}
	}
}