#include "arena.h"
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

	Arena* arena = new MyArena();
	
	Params colParams;
	colParams["radius"] = new ParamFloat(5.1f);

	Collision* collision = CreateEntity<Collision>("MyCollision", colParams);
	
	Movement movement(arena);
	Disease* disease = new MyDisease();
	
	Simulation sim(300, arena, collision, &movement, disease);

	InitGLViewer(argc, argv, &sim);

	return 0;
}
