#include "hospitalDisease.h"
#include "random.h"

#include <random>
#include <algorithm>
#include <iostream>

HospitalDisease::HospitalDisease(const Params& params)
	: Disease(params.get<float>("disease.transmitionRate",  0.1f),
		      params.get<int>("disease.numInitialInfected", 1))
	, _cureTime        (params.get<int>  ("disease.cureTime", 1000))
	, _symptomaticRate (params.get<float>("disease.symptomaticRate", 0.1f))
	, _symptomaticTime (params.get<int>  ("disease.symptomaticTime", 100))
	, _hospitalRate    (params.get<float>("disease.hospitalRate", 0.1f))
	, _hospitalTime    (params.get<int>  ("disease.hospitalTime", 100))
	, _deathRate	   (params.get<float>("disease.deathRate", 0.1f))
	, _deathTime	   (params.get<int>  ("disease.deathTime", 100))
{}

HospitalDisease::~HospitalDisease() {}

void
HospitalDisease::transmit(AgentsPairVec& agentPairs)
{
	for (auto& ap : agentPairs) {
		Agent& agentA = ap.first;
		Agent& agentB = ap.second;

		if (agentA.isInfected() || agentB.isInfected()) {
			if (SampleProbability(_transmissionRate)) {
				if (agentA.isSusceptible()) { agentA.infect(); }
				if (agentB.isSusceptible()) { agentB.infect(); }
			}
		}
	}
}

void
HospitalDisease::step()
{
	for (size_t i = 0; i < _simulation->getNumAgents(); ++i) {
		auto& agent = _simulation->getAgents()[i];

		// Nothing to do if the agent is dead
		if (agent.isDead()) {
			continue;
		}

		// Update infection
		if (agent.isInfected()) {
			// Update the age of the infection
			int age = agent.infectionAge++;

			// Get the agent category
			Category category = _categories[i];

			if (category == Category::Dead && age > _deathTime) {
				agent.kill();
				continue;
			} else if (category == Category::Hospitalized && age > _hospitalTime) {
				agent.hospitalize();
			} else if (category == Category::Symptomatic && age > _symptomaticTime) {
				agent.startSymptoms();
			}
			
			// Cure the agents that have been sick longer than the cure time
			if (category != Category::Dead && age > _cureTime) {
				agent.cure();
			}			
		}
	}
}

void
HospitalDisease::init()
{
	Disease::init();

	size_t numAgents = _simulation->getNumAgents();
	_categories.reserve(numAgents);

	// The absolute rates (since they are relative to each others)
	float absSymptomaticRate = _symptomaticRate;
	float absHospitalRate    = absSymptomaticRate * _hospitalRate;
	float absDeathRate       = absHospitalRate * _deathRate;

	// The number of agents on each category
	size_t numSymptomatic  = size_t(numAgents * absSymptomaticRate);
	size_t numHospitalized = size_t(numAgents * absHospitalRate);
	size_t numDead         = size_t(numAgents * absDeathRate);

	// Assign categories
	for (size_t i = 0; i < numAgents; ++i) {
		if (i < numDead) {
			_categories.push_back(Category::Dead);
	    } else if (i < numHospitalized) {
			_categories.push_back(Category::Hospitalized);
		} else if (i < numSymptomatic) {
			_categories.push_back(Category::Symptomatic);
		} else {
			_categories.push_back(Category::Asymptomatic);
		}
	}

	// Shuffle categories
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(_categories.begin(), _categories.end(), g);
}
