#include "arenaRenderer.h"

#include <SDL_opengl.h>

ArenaRenderer::ArenaRenderer(Simulation* sim)
	: GLRenderer(sim)
{
}

ArenaRenderer::~ArenaRenderer()
{
}

void ArenaRenderer::render()
{
	// TODO: move this call to  a place in run.cpp in a central heartbeat cycle
	_sim->step();

	glClearColor(0.0, 0.0, 0.0, 0.0);
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

	if (_renderInfected) {
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
}
