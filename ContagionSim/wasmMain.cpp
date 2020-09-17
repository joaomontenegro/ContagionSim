#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "run.h"

#include "param.h"
#include "paramFile.h"
#include "factory.h"
#include "log.h"

#include <emscripten/emscripten.h>

#include <cstdlib>
#include <ctime>

#include <memory>

typedef struct Args {
	Simulation* sim;
	Run* run;
} Args;

void mainLoop(void* args);

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));
	Log::setLogLevel(Log::LogLevel::Info);


	// TODO implement reading file in wasm?
	// Read Params
	/*
	Params params;
	params.set<std::string>("collision", "GridCollision");
	params.set<std::string>("movement",  "SimpleMovement");
	params.set<std::string>("disease",   "HospitalDisease");
	params.set<float>("collision.radius",   2.0f);
	params.set<float>("collision.gridSize", 5.0f);
	params.set<int>("simulation.numAgents", 1000);
	params.set<float>("simulation.width",  800);
	params.set<float>("simulation.height", 600);
	params.set<std::string>("execution.type", "GL");
	*/

	// Read Params
	Params params;
	if (!ReadParam("Params/contagion.params", &params)) {
		return 1;
	}

	// Simulation
	Simulation* sim = new Simulation(params);
	if (!sim->isValid()) {
		Log::error("Invalid Simulation - terminating...");
		return -1;
	}

	// Get the execution mode
	Run* run = nullptr;
	std::string executionType = params.get<std::string>("execution.type", "Console");
	if (executionType == "Console") {
		Log::info("Console Mode");
		run = new ConsoleRun(sim);
	}
	else if (executionType == "GL") {
		Log::info("GL Window Mode");
		int fps = params.get<int>("execution.fps", 60);
		run = new GLWindowRun(sim, fps);
	}

	// Main Loop
	Args args{ sim, run };
	emscripten_set_main_loop_arg(mainLoop, (void*)&args, 0, 1);

	delete run;
	delete sim;

	return 0;
}

void mainLoop(void* args)
{
	Args* argsPair = (Args *)args;
	argsPair->sim->step();
	argsPair->run->output();
}
