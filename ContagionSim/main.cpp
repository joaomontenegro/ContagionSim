#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "glviewer.h"

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
	if (argc < 2) {
		Log::warn(std::string("Usage: ") + argv[0] + " [PARAMS FILE]");
		return 1;
	}	
	std::string filepath = argv[1];

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

	// Run simulation in the viewer
	InitGLViewer(argc, argv, &sim);


	return 0;
}

