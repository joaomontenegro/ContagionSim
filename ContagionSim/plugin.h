#ifndef _PLUGIN_H_
#define _PLUGIN_H_

class Plugin
{
public:
	void setSimulation(Simulation* sim)
	{
		_simulation = sim;
		init();
	}

protected:
	virtual void init() = 0;
	Simulation* _simulation = nullptr;
};

#endif
