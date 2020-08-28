#include "glviewer.h"
#include "contagion.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <vector>

Simulation* _sim = nullptr;
bool renderInfected = false;
int step = 0;
GLuint _arenaWindowId;
GLuint _chartWindowId;

typedef struct
{
	size_t numSusceptible;
	size_t numAsymptomatic;
	size_t numSymptomatic;
	size_t numHospitalized;
	size_t numCured;
	size_t numDead;
} Totals;
std::vector<Totals> _totals;

void _displayArena()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, _sim->getWidth() , 0.0, _sim->getHeight());

	glClear(GL_COLOR_BUFFER_BIT);

	// Susceptible - White
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (auto& agent : _sim->getAgents()) {
		if (agent.isSusceptible()) {
			glVertex2f(agent.x, agent.y);
		}
	}
	glEnd();

	if (renderInfected) {
		// Infected - Red
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isInfected()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();
	}
	else {

		// Asymptomatic - Yellow
		glColor3f(0.75, 0.75, 0.0);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isAsymptomatic()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		// Symptomatic - Orange
		glColor3f(1.0f, 0.65f, 0.0f);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isSymptomatic()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		// Hospitalized - Red
		glColor3f(0.8f, 0.0f, 0.0f);
		glPointSize(5);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isHospitalized()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

	}
	
	// Dead - Grey
	glColor3f(0.5, 0.5, 0.5);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (auto& agent : _sim->getAgents()) {
		if (agent.isDead()) {
			glVertex2f(agent.x, agent.y);
		}
	}
	glEnd();

	// Cured - Green
	glColor3f(0.0, 0.5, 0.0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (auto& agent : _sim->getAgents()) {
		if (agent.isCured()) {
			glVertex2f(agent.x, agent.y);
		}
	}

	glEnd();
	glFlush();
	//glutSwapBuffers();
}


void _displayChart()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	float step = 1.0f / _totals.size();
	float x = 0.0f;

	// Dead
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		size_t value = t.numDead + t.numCured + t.numHospitalized + t.numSymptomatic + t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Cured
	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		size_t value = t.numCured + t.numHospitalized + t.numSymptomatic + t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Hospitalized
	glColor3f(0.8f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		size_t value = t.numHospitalized + t.numSymptomatic + t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Symptomatic
	glColor3f(1.0f, 0.65f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		size_t value = t.numSymptomatic + t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Asymptomatic
	glColor3f(0.8f, 0.8f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		size_t value = t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	
	glFlush();
	//glutSwapBuffers();

}


void _arenaTimer(int value)
{
	// Execute one simulation step
	step++;
	auto startTime = std::chrono::system_clock::now();
	_sim->step();
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = endTime - startTime;

	// Print values
	std::cout << std::setprecision(5) << "\r"
		<< "Step: " << step << "   "
		<< "fps: " << 1.0 / elapsedTime.count() << "   "
		<< "Susceptible: " << _sim->getNumSusceptible() << "   "
		<< "Infected: " << _sim->getNumInfected() << "   "
		<< "Cured: " << _sim->getNumCured() << "   "
		<< "Dead: " << _sim->getNumDead()
		<< "            " << std::flush;

	// Draw Window
	//glutSetWindow(_arenaWindowId);
	//glutPostRedisplay();

	// Reset the timer
	if (_sim->getNumInfected() > 0) {
		//glutTimerFunc(1, _arenaTimer, 0);
	}
}

void _chartTimer(int value)
{
	Totals newTotals = {
		_sim->getNumSusceptible(),
		_sim->getNumAsymptomatic(),
		_sim->getNumSymptomatic(),
		_sim->getNumHospitalized(),
		_sim->getNumCured(),
		_sim->getNumDead()
	};

	_totals.push_back(newTotals);

	//glutSetWindow(_chartWindowId);
	//glutPostRedisplay();

	// Reset the timer
	if (_sim->getNumInfected() > 0) {
		//glutTimerFunc(50, _chartTimer, 0);
	}
}

SDL_Window* _initWindow(int width, int height, const std::string& title)
{
	SDL_Window* displayWindow;
	SDL_Renderer* displayRenderer;
	SDL_RendererInfo displayRendererInfo;
	
	SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &displayWindow, &displayRenderer);
	if (!displayWindow) {
		Log::error("Failed to create window: " + title + " : " + SDL_GetError());
		return nullptr;
	}

	SDL_SetWindowTitle(displayWindow, title.c_str());
	
	if (!displayRenderer) {
		Log::error("Failed to create renderer for: " + title + " : " + SDL_GetError());
		return nullptr;
	}

	SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
	/*TODO: Check that we have OpenGL */
	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		Log::error("No OpenGL for: " + title + " : " + SDL_GetError());
		return nullptr;
	}

	// Init GL
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// TODO!!
	// Init Viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);


	// TODO
	// Render Arena 
	//_displayArena();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO move to loop for all windows
	bool keepOpen = true;
	while (keepOpen)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				keepOpen = false;
				break;
			}

			SDL_UpdateWindowSurface(displayWindow);
		}
	}

    return displayWindow;
}

void _initArenaWindow(Simulation* sim)
{
	float aspectRatio = _sim->getWidth() / _sim->getHeight();

	int width = 1000;
	int height = int(1000.0f / aspectRatio);

	SDL_Window* window = _initWindow(width, height, "ContagionSim - Arena");

	//glutInitDisplayMode(//glut_SINGLE | glut_RGB);
	//glutInitWindowSize(width, height);
	//glutInitWindowPosition(100, 100);
	//_arenaWindowId = glutCreateWindow("Points");
	//glutInitDisplayMode(//glut_RGBA | glut_DOUBLE);
	//glutDisplayFunc(_displayArena);
	
}


void _initChartWindow(Simulation* sim)
{
	//glutInitDisplayMode(//glut_SINGLE | glut_RGB);
	//glutInitWindowSize(600, 400);
	//glutInitWindowPosition(1200, 200);
	//_chartWindowId = glutCreateWindow("Points");
	//glutInitDisplayMode(//glut_RGBA | glut_DOUBLE);
	//glutDisplayFunc(_displayChart);
}


void RunGL(int argc, char** argv, Simulation* sim)
{
    _sim = sim;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Log::error("Failed to initialize the SDL2 library");
	}
	
	_initArenaWindow(_sim);
	//_initChartWindow(_sim);
}
