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
	Log::info("Running in the Console");

	size_t step = 0;
	for (; sim->getNumInfected() > 0; sim->step(), ++step) {
		_PrintSimulation(sim, step);
	}
	
	// Print one last time
	_PrintSimulation(sim, step);
}

void RunGL(Simulation* sim, int fps)
{
	Log::info("Running in GL mode.");

	// Create the renderers
	ArenaRenderer arenaRenderer(sim);
	//ChartRenderer chartRenderer(sim);


	// Create the Window
	GLWindow arenaWindow("ContagionSim - Arena",
		(int)sim->getWidth(), (int)sim->getHeight(),
		&arenaRenderer);

	// Time variables
	float frameTime = 1000.0f / fps;
	Uint32 prevTicks = SDL_GetTicks();

	// Main loop
	size_t step = 0;
	for (; sim->getNumInfected() > 0; sim->step(), ++step) {
		// Exit if the window is closed
		if (!arenaWindow.processEvents()) { break; }

		// Render on the right time to maintain the fps
		Uint32 curTicks = SDL_GetTicks();
		if (curTicks - prevTicks >= frameTime) {			
			arenaWindow.draw();
			prevTicks = curTicks;
		}
	}
}

void Run(Simulation* sim, const Params& params)
{
	std::string executionType = params.get<std::string>("execution.type", "Console");
	if (executionType == "Console") {
		RunConsole(sim);
	}
	else if (executionType == "GL") {
		int fps = params.get<int>("execution.fps", 60);
		RunGL(sim, fps);
	}
	else {
		Log::error("Invalid Execution Type: " + executionType);
	}
}
