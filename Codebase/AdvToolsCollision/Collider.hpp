#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
//#include "AABB.hpp"
//#include "Sphere.hpp"

class AABB;
class Sphere;

class Collider : public GameObject {


	public:
		Collider(float radius, bool aabb);
		~Collider();

		// ADD VIRTUAL KEYWORD TO USE DOUBLE DISPATCH. LEAVE VIRTUAL OUT TO USE SWITCH
		virtual bool checkCollision(Collider* pCollider) const;


		bool checkCircleCircleCollision(Collider* pCollider) const;
		bool checkAABBCircleCollision(Collider* pCollider) const;
		bool checkCircleAABBCollision(Collider* pCollider) const;
		bool checkAABBAABBCollision(Collider* pCollider) const;

		virtual bool checkCollision(AABB* pCollider) const;
		virtual bool checkCollision(Sphere* pCollider) const;

		float getRadius() const;
		bool getIsAABB() const;
	protected:
		float radius;
		bool isAABB;


};

#endif // COLLIDER_HPP
