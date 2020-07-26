#include "glviewer.h"
#include "contagion.h"

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
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(_sim->getCollision()->getRadius());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, _sim->getWidth() , 0.0, _sim->getHeight());

	glClear(GL_COLOR_BUFFER_BIT);

	// Susceptible - Green
	glColor3f(0.0, 0.75, 0.0);
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
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isAsymptomatic()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		// Symptomatic - Orange
		glColor3f(1.0, 0.65, 0.0);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isSymptomatic()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		// Hospitalized - Red
		glColor3f(0.8, 0.0, 0.0);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isHospitalized()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

	}
	
	// Dead - Grey
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (auto& agent : _sim->getAgents()) {
		if (agent.isDead()) {
			glVertex2f(agent.x, agent.y);
		}
	}
	glEnd();

	// Cured - Blue
	glColor3f(0, 0.0, 0.85);
	glBegin(GL_POINTS);
	for (auto& agent : _sim->getAgents()) {
		if (agent.isCured()) {
			glVertex2f(agent.x, agent.y);
		}
	}

	glEnd();
	glFlush();
	glutSwapBuffers();
}


void _displayChart()
{
	glClearColor(0.0, 0.5, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	float step = 1.0f / _totals.size();
	float x = 0.0f;

	// Asymptomatic
	glColor3f(0.8, 0.8, 0.0);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		int value = t.numDead + t.numCured + t.numHospitalized + t.numSymptomatic + t.numAsymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Symptomatic
	glColor3f(1.0, 0.65, 0.0);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		int value = t.numDead + t.numCured + t.numHospitalized + t.numSymptomatic;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Hospitalized
	glColor3f(0.8, 0.0, 0.0);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		int value = t.numDead + t.numCured + t.numHospitalized;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	// Cured
	glColor3f(0.0f, 0.0f, 0.85f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		int value = t.numDead + t.numCured;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();


	// Dead
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	x = 0.0f;
	for (auto& t : _totals) {
		int value = t.numDead;
		glVertex2f(x, 0.0f);
		glVertex2f(x, float(value) / _sim->getNumAgents());
		x += step;
	}
	glEnd();

	glFlush();
	glutSwapBuffers();

}


void _timer(int value)
{
	// Execute one simulation step
	step++;
	auto startTime = std::chrono::system_clock::now();
	_sim->step();
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = endTime - startTime;

	Totals newTotals = {
		_sim->getNumSusceptible(),
		_sim->getNumAsymptomatic(),
		_sim->getNumSymptomatic(),
		_sim->getNumHospitalized(),
		_sim->getNumCured(),
		_sim->getNumDead()
	};

	_totals.push_back(newTotals);

	// Print values
	std::cout << std::setprecision(5) << "\r"
		<< "step: " << step << "   "
		<< "fps: " << 1.0 / elapsedTime.count() << "   "
		<< "Susceptible: " << _sim->getNumSusceptible() << "   "
		<< "Infected: " << _sim->getNumInfected() << "   "
		<< "Cured: " << _sim->getNumCured() << "   "
		<< "Dead: " << _sim->getNumDead()
		<< "            " << std::flush;


	// Draw Windows
	glutSetWindow(_arenaWindowId);
	glutPostRedisplay();
	glutSetWindow(_chartWindowId);
	glutPostRedisplay();

	// Reset the timer
	glutTimerFunc(1, _timer, 0);
}

void _initArenaWindow(Simulation* sim)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(int(_sim->getWidth()), int(_sim->getHeight()));
	glutInitWindowPosition(200, 200);
	_arenaWindowId = glutCreateWindow("Points");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutDisplayFunc(_displayArena);
	
}


void _initChartWindow(Simulation* sim)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(1200, 200);
	_chartWindowId = glutCreateWindow("Points");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutDisplayFunc(_displayChart);
}


void InitGLViewer(int argc, char** argv, Simulation* sim)
{
	_sim = sim;
	
	glutInit(&argc, argv);
	
	_initArenaWindow(_sim);
	_initChartWindow(_sim);

	glutTimerFunc(0, _timer, 0);
	glutMainLoop();
}
