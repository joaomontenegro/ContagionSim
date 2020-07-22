#ifndef _GRID_COLLISION_H_
#define _GRID_COLLISION_H_

#include "factory.h"
#include "param.h"
#include "collision.h"

#include <vector>

class GridCollision : public Collision
{
public:
	GridCollision(const Params& params);
	virtual ~GridCollision();

	virtual void collide(AgentsPairVec& result);

private:
	typedef std::vector<Agent*> Cell;
	typedef std::vector<Cell> Grid;

	inline bool calcCollision(const Agent& a, const Agent& b);
	void initGrid();
	void rebuildGrid();
	inline size_t getCell(const Agent& a);
	inline size_t getCell(size_t x, size_t y);
	void getAdjacentCells(const Agent& a, std::vector<size_t>& indices);
	void collideWithCell(Agent& agent, const Cell& cell, AgentsPairVec& result);

	float _gridSize;
	size_t _nCols = 1;
	size_t _nRows = 1;
	
	Grid _grid;
};

namespace {
	RegisterEntity<Collision, GridCollision> _GridCollision("GridCollision");
};



#endif