#include "CollisionManager.hpp"
#include "mge/config.hpp"


CollisionManager::CollisionManager() : testAmount(0) {

}


CollisionManager::~CollisionManager() {
	delete(redMaterial);
	delete(greenMaterial);
}

void CollisionManager::addCollider(Collider* pCollider) {
	_colliders.push_back(pCollider);
}

void CollisionManager::removeCollider(Collider* pCollider) {
	_colliders.push_back(pCollider);
	_colliders.erase(std::remove(_colliders.begin(), _colliders.end(), pCollider));
}

int CollisionManager::checkCollisions() {
	int total = 0;
	testAmount = 0;

	if (!config::USE_IGNOREHISTORY) {
		total = checkCollisionsUnoptimized();
	}
	else {
		total = checkCollisionsIgnoreHistory();
	}


	return total;
}

int CollisionManager::checkCollisionsUnoptimized() {
	int total = 0;
	for (int i = 0; i < _colliders.size(); i++) {
		// If no collisions, this will stay until the end
		_colliders[i]->setMaterial(redMaterial);
		for (int j = 0; j < _colliders.size(); j++) {
			if (i != j) {
				testAmount++;
				if (_colliders[i]->checkCollision(_colliders[j])) {
					total++;
					//_colliders[i]->setMaterial(mats[_colliders[i].colTotal]); or 
					// If there's a collision, set to appropiate colour
					_colliders[i]->setMaterial(greenMaterial);
				}
			}
		}
	}

	return total;
}

int CollisionManager::checkCollisionsIgnoreHistory() {
	for (int i = 0; i < _colliders.size(); i++) {
		// If no collisions, this will stay until the end
		//_colliders[i]->setMaterial(redMaterial);
	}

	int total = 0;

	for (int i = 0; i < _colliders.size(); i++) {
		for (int j = i + 1; j < _colliders.size(); j++) {
			if (i != j) {
				testAmount++;
				if (_colliders[i]->checkCollision(_colliders[j])) {
					total++;
					// If there's a collision, set to appropiate colour
					
					if (_colliders[i]->isColliding == false) {
						int iCellX = _colliders[i]->cellX;
						int iCellY = _colliders[i]->cellY;
						int jCellX = _colliders[j]->cellX;
						int jCellY = _colliders[j]->cellY;
						int iGrid = _colliders[i]->gridNr;
						int jGrid = _colliders[j]->gridNr;

						bool xIsSame = iCellX == jCellX;
						bool yIsSame = iCellY == jCellY;
						bool gridIsSame = iGrid == jGrid;

						//printf("\n\t\tX: %f \t Y: %f \t Grid %i, Cell %i %i    \n", _colliders[i]->getWorldPosition().x, _colliders[i]->getWorldPosition().z, _colliders[i]->gridNr, iCellX, iCellY);
						//printf("\t\tX: %f \t Y: %f \t Grid %i, Cell %i %i \n", _colliders[j]->getWorldPosition().x, _colliders[j]->getWorldPosition().z, _colliders[j]->gridNr, jCellX, jCellY);
						printf("%s %s \t%s \t", xIsSame ? "true" : "false", yIsSame ? "true" : "false", gridIsSame ? "true" : "false");
						printf("Cell X: %i %i \t Y: %i %i \t Grid: %i %i\n", iCellX, jCellX, iCellY, jCellY, iGrid, jGrid);
						if (iCellY == jCellY) {
							for (int i = 0; i < 10; i++) {
								printf("ATTENTION!!!!\n\n\n\n\n\n\n\n\n\n");
							}
						}
					}
					
					
					//_colliders[i]->setMaterial(greenMaterial);
					//_colliders[j]->setMaterial(greenMaterial);
				}
			}
		}
	}
	//printf("Finished a round");

	return total;
}

int CollisionManager::getTestAmount() {
	return testAmount;
}