#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
//#include "Grid.hpp"
#include "GridManager.hpp"
//#include "AABB.hpp"
//#include "Sphere.hpp"

class AABB;
class Sphere;

class Collider : public GameObject {

	friend class GridManager;
	friend class Grid;
	public:
		Collider(float pX, float pY, float pRadius, bool pAabb);
		~Collider();


		virtual bool checkCollision(Collider* pCollider) const;


		bool checkCircleCircleCollision(Collider* pCollider) const;
		bool checkAABBCircleCollision(Collider* pCollider) const;
		bool checkCircleAABBCollision(Collider* pCollider) const;
		bool checkAABBAABBCollision(Collider* pCollider) const;

		virtual bool checkCollision(AABB* pCollider) const;
		virtual bool checkCollision(Sphere* pCollider) const;

		float getRadius() const;
		bool getIsAABB() const;

		glm::vec2 GetVec2Pos() const;

		void SetColMaterial(float r, float g, float b, float a);

		void ReloadMaterial();

		int cellX;
		int cellY;
		int gridNr;
		bool isColliding;
	protected:
		bool isAABB;

		// Filling memory gaps
		bool fillGap1 = false;
		bool fillGap2 = false;
		float fillGap3 = 0.0f;


		float radius;


		Collider* prev_;
		Collider* next_;

};

#endif // COLLIDER_HPP
