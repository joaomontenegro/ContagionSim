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
	std::vector<size_t> cellIndices;
	cellIndices.reserve(9);

	// Collision with other agents
	for (auto& agent : _simulation->getAgents()) {
		if (agent.isDead() || agent.isCured()) { continue; }
		
		cellIndices.clear();
		getAdjacentCells(agent, cellIndices);
		for (size_t cellIndex : cellIndices) {
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
		if (agent.isSusceptible() || agent.isInfected()) {
			size_t cell = getCell(agent);
			_grid[cell].push_back(&agent);
		}
	}
}

size_t
GridCollision::getCell(const Agent& a)
{
	size_t x = size_t(a.x / _gridSize);
	size_t y = size_t(a.y / _gridSize);
	return getCell(x, y);
}

size_t
GridCollision::getCell(size_t x, size_t y)
{
	return y * _nRows + x;
}

void
GridCollision::getAdjacentCells(const Agent& a, std::vector<size_t>& indices)
{
	float width = _simulation->getWidth();
	float height = _simulation->getHeight();

	// Relative coordinates of the grid
	size_t x = size_t(a.x / _gridSize);
	size_t y = size_t(a.y / _gridSize);

	// Absolute coordinates of the grid
	float fx = _gridSize * x;
	float fy = _gridSize * y;

	// If the radius intercepts the cells around
	bool prevX = (x > 0 && a.x - _radius < fx);
	bool prevY = (y > 0 && a.y - _radius < fy);
	bool nextX = (x < width  && a.x + _radius > fx + 1);
	bool nextY = (y < height && a.y + _radius > fy + 1);

	indices.push_back(getCell(x, y));

	if (prevX) {
		indices.push_back(getCell(x - 1, y));
		if (prevY) { indices.push_back(getCell(x - 1, y - 1)); }
		if (nextY) { indices.push_back(getCell(x - 1, y + 1)); }
	}
	else if (nextX) {
		indices.push_back(getCell(x + 1, y));
		if (prevY) { indices.push_back(getCell(x + 1, y - 1)); }
		if (nextY) { indices.push_back(getCell(x + 1, y + 1)); }
	}

	if (prevY) { indices.push_back(getCell(x, y - 1)); }
	if (nextY) { indices.push_back(getCell(x, y + 1)); }
}

void
GridCollision::collideWithCell(Agent& agent,
						       const Cell& cell,
						       AgentsPairVec& result)
{
	for (auto other : cell) {
		if (&agent >= other) { continue; }
		if (!agent.canSpread && other->canSpread) { continue; }
		if (other->isDead() || other->isCured()) { continue; }
		if (calcCollision(agent, *other)) {
			result.push_back(AgentsPair(agent, *other));
		}
	}
}
