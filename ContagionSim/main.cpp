#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "run.h"

#include "param.h"
#include "paramFile.h"
#include "factory.h"
#include "log.h"

#include <cstdlib>
#include <ctime>

#include <memory>


int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));
	Log::setLogLevel(Log::LogLevel::Info);

	// Get the params file path from the command line args
	std::string filepath;
	
	if (argc < 2) {
		Log::info(std::string("Usage: ") + argv[0] + " [PARAMS FILE]");
		
		filepath = "contagion.params";
	}
	else {
		filepath = argv[1];
	}

	// Read Params
	Params params;
	if (!ReadParam(filepath, &params)) {
		return 1;
	}

	// Simulation
	Simulation sim(params);
	if (!sim.isValid()) {
		Log::error("Invalid Simulation - terminating...");
		return -1;
	} 

	// Get the execution mode
	Run* run = nullptr;
	std::string executionType = params.get<std::string>("execution.type", "Console");
	if (executionType == "Console") {
		Log::info("Console Mode");		
		run = new ConsoleRun(&sim);
	}
	else if (executionType == "GL") {
		Log::info("GL Window Mode");
		int fps = params.get<int>("execution.fps", 60);
		run = new GLWindowRun(&sim, fps);
	}

	// Main Loop
	while (!run->hasEnded()) {
		sim.step();
		run->output();
	}

	delete run;

	return 0;
}
