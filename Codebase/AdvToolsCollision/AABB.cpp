#include "AABB.hpp"


AABB::AABB(float pX, float pY, float pRadius) : Collider(pX, pY, pRadius, true){

}
AABB::~AABB() {
	//dtor
}


bool AABB::checkCollision(Collider* pCollider) const {
	if (!config::USE_DOUBLEDISPATCH) {
		return Collider::checkCollision(pCollider);
	}
	return pCollider->checkCollision((AABB*)this);
}


bool AABB::checkCollision(AABB* pCollider) const {

	return checkAABBAABBCollision((Collider*)pCollider);
}

bool AABB::checkCollision(Sphere* pCollider) const {

	return checkAABBCircleCollision((Collider*)pCollider);

}