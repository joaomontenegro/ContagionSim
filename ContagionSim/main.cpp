#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "glviewer.h"

#include "param.h"
#include "factory.h"
#include "log.h"

#include <cstdlib>
#include <ctime>

#include <memory>
#include <iostream>

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));

	setLogLevel(LogLevel::Info);

	//TODO: divide params into groups instead of these points?
	Params params;
	params.set<std::string>("collision", "SimpleCollision");
	params.set<std::string>("movement",  "SimpleMovement");
	params.set<std::string>("disease",   "SimpleDisease");
	params.set<float>("collision.radius", 5.1f);
	params.set<float>("movement.width", 800.0f);
	params.set<float>("movement.height", 600.0f);
	params.set<float>("disease.rate", 0.1f);
	params.set<int>("simulation.numAgents", 200);

	// Simulation
	Simulation sim(params);
	if (!sim.isValid()) {
		error("Invalid Simulation - terminating...");
		return -1;
	} 

	// Run simulation in the viewer
	InitGLViewer(argc, argv, &sim);

	return 0;
}

