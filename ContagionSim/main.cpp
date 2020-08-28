#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "glviewer.h"
#include "run.h"

#include "param.h"
#include "paramFile.h"
#include "factory.h"
#include "log.h"

#include <cstdlib>
#include <ctime>

#include <memory>
#include <iostream>

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

	// Run simulation in GL or Console
	Run(&sim, params, true/*inWindow*/);

	return 0;
}
