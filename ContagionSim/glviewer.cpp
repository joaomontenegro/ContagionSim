#include "glviewer.h"
#include "contagion.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

Simulation* _sim = nullptr;

int windowX = 200;
int windowY = 200;

bool renderInfected = false;

int step = 0;

void _display()
{
	if (_sim == nullptr) return;

	// Execute one simulation step
	step++;
	auto startTime = std::chrono::system_clock::now();
	_sim->step();
	auto endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = endTime - startTime;

	std::cout << std::setprecision(5) << "\r"
		<< "step: " << step << "   "
		<< "fps: " << 1.0 / elapsedTime.count() << "   "
		<< "Susceptible: " << _sim->getNumSusceptible() << "   "
		<< "Infected: " << _sim->getNumInfected() << "   "
		<< "Cured: " << _sim->getNumCured() << "   "
		<< "Dead: " << _sim->getNumDead()
		<< "            " << std::flush;

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
		glColor3f(0.8, 0.8, 0.0);
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
	glColor3f(0.75, 0.75, 0.75);
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

void _mouse(int button, int state, int x, int y)
{
	std::cout << button << " : " << x << " , " << y << std::endl;
}

void _keyBoard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}
}

void timer(int value)
{
	glutTimerFunc(1, timer, 0);
	glutPostRedisplay();
}

void InitGLViewer(int argc, char** argv, Simulation* sim)
{
	_sim = sim;
	float width  = _sim->getWidth();
	float height = _sim->getHeight();
	float radius = _sim->getCollision()->getRadius();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(int(width), int(height));
	glutInitWindowPosition(windowX, windowY);
	glutCreateWindow("Points");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutTimerFunc(0, timer, 0);

	glutDisplayFunc(_display);
	glutKeyboardFunc(_keyBoard);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(radius);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glutMainLoop();
}
