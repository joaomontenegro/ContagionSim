#include "glviewer.h"
#include "contagion.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

Simulation* _sim = nullptr;
int STEPS = -1;

int windowX = 200;
int windowY = 200;
int windowId = -1;

void _display()
{
	if (_sim == nullptr) return;

	for (int i = 0; STEPS < 0 || i < STEPS; ++i) {
		
		auto startTime = std::chrono::system_clock::now();
		
		_sim->step();
		
		auto endTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedTime = endTime - startTime;

		std::cout << std::setprecision(4) << "\r"
		          << 1.0 / elapsedTime.count() << " fps   "
			      << "Susceptible: " << _sim->getNumSusceptible() << "   "
				  << "Infected: " << _sim->getNumInfected() << "   "
			      << "Cured: " << _sim->getNumCured()
			      << "            " << std::flush;


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
			if (agent.isSusceptible()) {
				glVertex2f(agent.x, agent.y);
			}
		}
		glEnd();

		glEnd();
		glFlush();

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void _mouse(int button, int state, int x, int y)
{
	std::cout << button << " : " << x << " , " << y << std::endl;
}

void _keyBoard(unsigned char key, int x, int y)
{
	if (key == 27) {
		std::cout << "Esc" << std::endl;
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
	glutInitWindowPosition(windowX, windowY);
	windowId = glutCreateWindow("Points");
	glutDisplayFunc(_display);
	glutMouseFunc(_mouse);
	glutKeyboardFunc(_keyBoard);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(radius);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	glutMainLoop();
}
