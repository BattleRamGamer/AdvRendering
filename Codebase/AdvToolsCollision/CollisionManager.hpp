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

	protected:
		std::vector<Collider*> _colliders;

		int testAmount;

		// Add colour textures here!!!
		AbstractMaterial* redMaterial = new ColorMaterial(glm::vec3(1, 0, 0));
		AbstractMaterial* greenMaterial = new ColorMaterial(glm::vec3(0, 1, 0));
};







#endif // COLLISIONMANAGER_HPP
