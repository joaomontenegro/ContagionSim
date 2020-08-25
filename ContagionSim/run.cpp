#include "run.h"

void _PrintValues(Simulation* sim, size_t step) {
	std::cout << std::setprecision(5) << "\r"
		<< "Step: " << step << "   "
		<< "Susceptible: " << sim->getNumSusceptible() << "   "
		<< "Infected: " << sim->getNumInfected() << "   "
		<< "Cured: " << sim->getNumCured() << "   "
		<< "Dead: " << sim->getNumDead()
		<< "            " << std::flush;
}

void RunConsole(Simulation* sim)
{
	size_t step = 0;
	for (; sim->getNumInfected() > 0; sim->step(), ++step) {
		_PrintValues(sim, step);
	}

	_PrintValues(sim, step);
}