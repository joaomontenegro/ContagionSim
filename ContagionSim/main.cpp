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

	Log::setLogLevel(Log::LogLevel::Info);

	Params params;

	// Plugin params
	//params.set<std::string>("collision", "SimpleCollision");
	params.set<std::string>("collision", "GridCollision");
	params.set<std::string>("movement",  "SimpleMovement");
	//params.set<std::string>("disease", "SimpleDisease");
	params.set<std::string>("disease",   "HospitalDisease");
	
	// Collision params
	params.set<float>("collision.radius", 5.0f);
	params.set<float>("collision.gridSize", 5.0f);
	
	// Movement params
	params.set<float>("movement.minSpeed", 0.1f);
	params.set<float>("movement.maxSpeed", 1.0f);	
	
	// Disease params
	params.set<int>  ("disease.numInitialInfected", 1);
	params.set<float>("disease.transmitionRate", 0.1f);
	params.set<float>("disease.symptomaticRate", 0.5f);
	params.set<int>  ("disease.symptomaticTime", 200);
	params.set<float>("disease.hospitalRate", 0.5f);
	params.set<int>  ("disease.hospitalTime", 500);
	params.set<float>("disease.deathRate", 0.5f); 
	params.set<int>  ("disease.deathTime", 1500);
	params.set<int>  ("disease.cureTime", 2000);
	// TODO hospital capacity
	// TODO death rate and times of non hospitalized
	// TODO add jitter to times

	// Simulation params
	params.set<int>  ("simulation.numAgents", 500);
	params.set<float>("simulation.width", 800.0f);
	params.set<float>("simulation.height", 600.0f);

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

