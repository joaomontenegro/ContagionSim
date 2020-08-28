#include "run.h"

#include "window.h"
#include "arenaRenderer.h"
#include "chartRenderer.h"

#include <sstream>

//TODO move step count into simulation
void _PrintSimulation(Simulation* sim, size_t step) {
	std::stringstream ss;
	ss << std::setprecision(5)
		<< "Step: " << step << "   "
		<< "Susceptible: " << sim->getNumSusceptible() << "   "
		<< "Infected: " << sim->getNumInfected() << "   "
		<< "Cured: " << sim->getNumCured() << "   "
		<< "Dead: " << sim->getNumDead();

	Log::print(ss.str());
}

void RunConsole(Simulation* sim)
{
	Log::info("Running in Console mode.");

	size_t step = 0;
	for (; sim->getNumInfected() > 0; sim->step(), ++step) {
		_PrintSimulation(sim, step);
	}
	
	// Print one last time
	_PrintSimulation(sim, step);
}

void RunGL(Simulation* sim, bool inWindow)
{
	Log::info("Running in GL mode.");

	// TODO might have to go into the if statement below
	// Create the renderers
	ArenaRenderer arenaRenderer(sim);
	//ChartRenderer chartRenderer(sim);

	//TODO use a central cycle that renders all windows?

	if (inWindow) {
		// Window mode
		Log::info("  Running in a Window.");
		GLWindow arenaWindow("ContagionSim - Arena",
			(int)sim->getWidth(),
			(int)sim->getHeight(),
			&arenaRenderer);
		
		arenaWindow.show();		

	} else {
		// Init surface?
		Log::info("Running in Console.");

		// TODO WASM 
	}
}

void Run(Simulation* sim, const Params& params, bool inWindow)
{
	std::string executionType = params.get<std::string>("execution.type", "Console");
	if (executionType == "Console") {
		RunConsole(sim);
	}
	else if (executionType == "GL") {
		RunGL(sim);
	}
	else {
		Log::error("Invalid Execution Type: " + executionType);
	}
}
