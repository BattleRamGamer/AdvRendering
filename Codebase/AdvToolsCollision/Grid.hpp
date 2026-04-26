#ifndef GRID_HPP
#define GRID_HPP


#include "MoveBehaviour.hpp"
#include "Collider.hpp"

class Collider;
class Grid {

public:
	Grid();
	~Grid();

	void Add(Collider* pCollider);

	void handleCollisions();
	void handleCell(Collider* pCollider);

private:
	Collider* cells_[config::GRID_COLUMN_COUNT][config::GRID_ROW_COUNT];


};



#endif // GRID_HPP
