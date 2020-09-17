#include "arenaRenderer.h"

ArenaRenderer::ArenaRenderer(Simulation* sim)
	: GLRenderer(sim)
{
	_positions = new SDL_Point[sim->getNumAgents()];
}

ArenaRenderer::~ArenaRenderer()
{
	delete[] _positions;
}

void ArenaRenderer::render(SDL_Renderer* sdlRenderer)
{
	SDL_SetRenderDrawColor(sdlRenderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(sdlRenderer);

	// Susceptible - White
	for (size_t i = 0; i < _sim->getNumAgents(); ++i) {
		// TODO: sort points by agent state
		Agent& agent = _sim->getAgent(i);
		_positions[i] = {(int)agent.x, (int)agent.y};
	}

	// TODO: SDL_RenderSetScale(sdlRenderer, 3, 3);

    int pos = 0;
	int len = (int)_sim->getNumSusceptible();
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);
	pos += len;

	// Asymptomatic - Yellow
	len = (int)_sim->getNumAsymptomatic();
	SDL_SetRenderDrawColor(sdlRenderer, 0xC0, 0xC0, 0x0, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);
	pos += len;

	// Symptomatic - Orange
	len = (int)_sim->getNumSymptomatic();
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xA6, 0x0, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);
	pos += len;

	// Hospitalized - Red
	len = (int)_sim->getNumHospitalized();
	SDL_SetRenderDrawColor(sdlRenderer, 0xCC, 0x0, 0x0, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);
	pos += len;

	// Dead - Grey
	len = (int)_sim->getNumDead();
	SDL_SetRenderDrawColor(sdlRenderer, 0x7F, 0x7F, 0x7F, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);

	// Cured - Green
	len = (int)_sim->getNumCured();
	SDL_SetRenderDrawColor(sdlRenderer, 0x0, 0x80, 0x0, 0xFF);
	SDL_RenderDrawPoints(sdlRenderer, _positions, len);

	SDL_RenderPresent(sdlRenderer);
}
