#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include "Collider.hpp"
#include "mge/materials/ColorMaterial.hpp"

class CollisionManager {


	public:
		CollisionManager();
		virtual ~CollisionManager();

		virtual void addCollider(Collider* pCollider);
		void removeCollider(Collider* pCollider);
		int checkCollisions();
		int checkCollisionsUnoptimized();
		int checkCollisionsIgnoreHistory();

		int getTestAmount();
		int getCollisionAmount();

		void independentCollisionCheck(int pI, int pJ);

	protected:
		std::vector<Collider*> _colliders;

		int testAmount;
		int collisionAmount;

};







#endif // COLLISIONMANAGER_HPP
