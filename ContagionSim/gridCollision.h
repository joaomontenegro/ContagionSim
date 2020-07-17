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
	inline size_t getCellIndex(const Agent& a);
	void getCellIndicesAround(const Agent& a, std::vector<size_t>& indices);
	void collideWithCell(Agent& agent, const Cell& cell, AgentsPairVec& result);

	float _gridSize;
	size_t _nCols;
	size_t _nRows;
	
	Grid _grid;
	std::vector<size_t> _cellIndices;

};

namespace {
	RegisterEntity<Collision, GridCollision> _GridCollision("GridCollision");
};



#endif