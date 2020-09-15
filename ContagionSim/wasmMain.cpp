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
#include <iostream>

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));
	Log::setLogLevel(Log::LogLevel::Info);

	// TODO implement reading file in wasm?
	// Read Params
	Params params;
	params.set<std::string>("collision", "GridCollision");
	params.set<std::string>("movement",  "SimpleMovement");
	params.set<std::string>("disease",   "HospitalDisease");
	params.set<float>("collision.radius",   2.0f);
	params.set<float>("collision.gridSize", 5.0f);
	params.set<int>("simulation.numAgents", 1000);
	params.set<float>("simulation.width",  800);
	params.set<float>("simulation.height", 600);

	// Simulation
	Simulation sim(params);
	if (!sim.isValid()) {
		Log::error("Invalid Simulation - terminating...");
		return -1;
	}

	// Run simulation in GL or Console
	Run(&sim, params);

	Log::info("Done.");

	return 0;
}

