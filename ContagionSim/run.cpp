#include "run.h"

#include <sstream>
#include <iomanip>

ConsoleRun::ConsoleRun(Simulation* sim) : Run(sim) {}

ConsoleRun::~ConsoleRun() {}

bool ConsoleRun::hasEnded()
{
	return _sim->getNumInfected() == 0;
}


void ConsoleRun::output()
{
	std::stringstream ss;
	ss << std::setprecision(5)
		<< "Step: " << _sim->getStepCount() << "   "
		<< "Susceptible: " << _sim->getNumSusceptible() << "   "
		<< "Infected: " << _sim->getNumInfected() << "   "
		<< "Cured: " << _sim->getNumCured() << "   "
		<< "Dead: " << _sim->getNumDead();

	Log::print(ss.str());
}


GLWindowRun::GLWindowRun(Simulation* sim, size_t fps)
	: Run(sim)
	, _frameDuration(1000 / fps)
	, _arenaRenderer(sim)
	, _arenaWindow(
		"ContagionSim - Arena",
		(int)sim->getWidth(), (int)sim->getHeight(),
		&_arenaRenderer)
{}

GLWindowRun::~GLWindowRun() {}


bool GLWindowRun::hasEnded()
{
	return !_arenaWindow.processEvents() || _sim->getNumInfected() == 0;
}


void GLWindowRun::output()
{
	if (_arenaWindow.getTimeSinceLastDraw() > _frameDuration) {
		_arenaWindow.draw();
		Log::info("Step " + std::to_string(_sim->getStepCount()));
	}		
}

