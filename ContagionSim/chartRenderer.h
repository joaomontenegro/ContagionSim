#ifndef _CHART_RENDERER_H_
#define _CHART_RENDERER_H_

#include "renderer.h"

class ChartRenderer : public GLRenderer
{
public:
	ChartRenderer(Simulation* sim) : GLRenderer(sim) {}
	virtual ~ChartRenderer() {}

public:
	void render(SDL_Renderer* sdlRenderer) override {/*TODO*/}
};

#endif
