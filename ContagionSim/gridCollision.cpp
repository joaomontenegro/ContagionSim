#include "gridCollision.h"
#include "log.h"

#include <math.h>

GridCollision::GridCollision(const Params& params)
	: Collision(params.get<float>("collision.radius", 3.5f))
	, _gridSize(params.get<float>("collision.gridSize", 20.0f))
{
	if (_radius > _gridSize) {
		std::string msg = "collision.radius > collision.gridSize : ";
		msg += std::to_string(_radius) + " > " + std::to_string(_gridSize);
		msg += ". Setting gridSize = radius...";
		Log::warn(msg);
		_gridSize = _radius;
	}
}

GridCollision::~GridCollision() {}

void
GridCollision::collide(AgentsPairVec& result)
{
	rebuildGrid();

	// Collision with other agents
	for (auto& agent : _simulation->getAgents()) {
		_cellIndices.clear();
		getCellIndicesAround(agent, _cellIndices);
		for (size_t cellIndex : _cellIndices) {
			collideWithCell(agent, _grid[cellIndex], result);
		}
	}
}

bool
GridCollision::calcCollision(const Agent& a, const Agent& b)
{
	if (&a == &b) { return false; }
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2) < _radius2;
}

void
GridCollision::initGrid()
{
	_nCols = size_t(ceil(_simulation->getWidth() / _gridSize));
	_nRows = size_t(ceil(_simulation->getHeight() / _gridSize));
	_grid.resize(_nCols * _nRows);
	_cellIndices.reserve(9);
}

void
GridCollision::rebuildGrid()
{
	if (_grid.empty()) {
		initGrid();
	}
	else {
		for (auto& cell : _grid) {
			cell.clear();
		}
	}
	
	for (auto& agent : _simulation->getAgents()) {
		size_t cell = getCellIndex(agent);
		_grid[cell].push_back(&agent);
	}
}

size_t
GridCollision::getCellIndex(const Agent& a)
{
	int x = int(a.x / _nCols);
	int y = int(a.y / _nRows);
	return y * _nCols + x;
}

void
GridCollision::getCellIndicesAround(const Agent& a, std::vector<size_t>& indices)
{
	indices.push_back(getCellIndex(a));
}

void
GridCollision::collideWithCell(Agent& agent,
						       const Cell& cell,
						       AgentsPairVec& result)
{
	for (auto other : cell) {
		if (calcCollision(agent, *other)) {
			result.push_back(AgentsPair(agent, *other));
		}
	}
}
