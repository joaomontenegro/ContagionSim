#ifndef _RUN_H_
#define _RUN_H_

#include "param.h"
#include "simulation.h"

#include <iostream>
#include <iomanip>

void RunConsole(Simulation* sim);

void RunGL(Simulation* sim);

void Run(Simulation* sim, const Params& params);

#endif

