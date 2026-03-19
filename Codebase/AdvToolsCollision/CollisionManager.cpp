#include "CollisionManager.hpp"
#include "mge/config.hpp"


CollisionManager::CollisionManager() {

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

	if (config::COL_DETECTION_TYPE == 0) {
		total = checkCollisionsUnoptimized();
	}
	else if (config::COL_DETECTION_TYPE == 1) {
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
		_colliders[i]->setMaterial(redMaterial);
	}

	int total = 0;

	for (int i = 0; i < _colliders.size(); i++) {
		for (int j = i + 1; j < _colliders.size(); j++) {
			if (i != j) {
				testAmount++;
				if (_colliders[i]->checkCollision(_colliders[j])) {
					total++;
					// If there's a collision, set to appropiate colour
					_colliders[i]->setMaterial(greenMaterial);
					_colliders[j]->setMaterial(greenMaterial);
				}
			}
		}
	}

	return total;
}

int CollisionManager::getTestAmount() {
	return testAmount;
}