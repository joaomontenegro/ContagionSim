#ifndef _HOSPITAL_DISEASE_H_
#define _HOSPITAL_DISEASE_H_

#include "param.h"
#include "factory.h"
#include "disease.h"

class HospitalDisease : public Disease
{
public:
	HospitalDisease(const Params& params);
	~HospitalDisease();

	void transmit(AgentsPairVec& agentPairs);

	void step();

protected:
	virtual void init();

private:
	int   _cureTime;
	float _symptomaticRate;
	int   _symptomaticTime;
	float _hospitalRate;
	int   _hospitalTime;
	float _deathRate;
	int   _deathTime;

	// Specify what will happen to each agent
	enum class Category { Asymptomatic, Symptomatic, Hospitalized, Dead };
	std::vector<Category> _categories;
};

namespace {
	RegisterEntity<Disease, HospitalDisease> _myDisease("HospitalDisease");
};

#endif // _HOSPITAL_DISEASE_H_
