#include "arena.h"
#include "collision.h"
#include "disease.h"
#include "movement.h"
#include "simulation.h"
#include "glviewer.h"

#include "factory.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

int main(int argc, char** argv) {
	srand((unsigned int)time(NULL));

	Arena arena(500, 500);
	Collision collision(5.0f);
	Movement movement(&arena);
	Disease disease(0.1f);
	Simulation sim(300, &arena, &collision, &movement, &disease);

	InitGLViewer(argc, argv, &sim);

	return 0;
}
