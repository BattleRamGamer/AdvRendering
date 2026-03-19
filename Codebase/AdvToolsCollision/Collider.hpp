#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "mge/core/GameObject.hpp"

class Collider : public GameObject {


	public:
		Collider(float radius, bool aabb);
		~Collider();

		bool checkCollision(Collider* pCollider) const;
		bool checkCircleCircleCollision(Collider* pCollider) const;
		bool checkAABBCircleCollision(Collider* pCollider) const;
		bool checkCircleAABBCollision(Collider* pCollider) const;
		bool checkAABBAABBCollision(Collider* pCollider) const;

		float getRadius() const;
		bool getIsAABB() const;
	private:
		float radius;
		bool isAABB;


};

#endif // COLLIDER_HPP
