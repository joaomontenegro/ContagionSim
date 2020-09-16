#ifndef _RUN_H_
#define _RUN_H_

#include "simulation.h"
#include "window.h"
#include "arenaRenderer.h"
#include "chartRenderer.h"

class Run
{
public:
	Run(Simulation* sim) : _sim(sim) {}
	virtual ~Run() {}

	virtual bool hasEnded() = 0;
	virtual void output() = 0;

protected:
	Simulation* _sim;
};

class ConsoleRun : public Run
{
public:
	ConsoleRun(Simulation* sim);
	virtual ~ConsoleRun();

	bool hasEnded() override;
	void output() override;
};


class GLWindowRun : public Run
{
public:
	GLWindowRun(Simulation* sim, size_t fps);
	virtual ~GLWindowRun();

	bool hasEnded() override;
	void output() override;

private:
	size_t _frameDuration;
	ArenaRenderer _arenaRenderer;
	GLWindow _arenaWindow;
};

#endif

