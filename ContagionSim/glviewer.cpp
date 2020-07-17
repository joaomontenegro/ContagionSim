#include "glviewer.h"
#include "contagion.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

Simulation* _sim = nullptr;
int STEPS = -1;

void _display()
{
	if (_sim == nullptr) return;

	for (int i = 0; STEPS < 0 || i < STEPS; ++i) {
		
		auto startTime = std::chrono::system_clock::now();
		
		_sim->step();
		
		auto endTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;
		std::cout << "\r" << 1.0 / elapsedTime.count() << " fps         " << std::flush;

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isInfected()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		glColor3f(0.75, 0.75, 0.0);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isCured()) {
				glVertex2f(agent.x, agent.y);
			}
		}

		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_POINTS);
		for (auto& agent : _sim->getAgents()) {
			if (agent.isHealthy()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		glEnd();
		glFlush();

		/*
		float infected = (float)_sim->getNumInfected() / (float)_sim->getNumAgents();
		float cured = (float)_sim->getNumCured() / (float)_sim->getNumAgents();
		std::cout << std::setprecision(2) << "Infected: " <<  infected << " | Cured: " << cured << std::endl;
		*/

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
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
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Points");
	glutDisplayFunc(_display);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(radius);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glutMainLoop();
}
