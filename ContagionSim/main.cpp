#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "glviewer.h"

#include "param.h"
#include "factory.h"

#include <cstdlib>
#include <ctime>

#include <memory>
#include <iostream>

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));

	// Collision
	Params colParams;
	colParams.set<float>("radius", 5.1f);
	Collision* collision = CreateEntity<Collision>("MyCollision", colParams);
	
	// Movement
	Params movParams;
	movParams.set<float>("width", 800.0f);
	movParams.set<float>("height", 600.0f);
	Movement* movement = CreateEntity<Movement>("MyMovement", movParams);
	
	// Disease
	Disease* disease = new MyDisease();
	
	// Simulation
	Params simParams;
	simParams.set<int>("numAgents", 200);
	Simulation sim(simParams, collision, movement, disease);

	InitGLViewer(argc, argv, &sim);

	return 0;
}

