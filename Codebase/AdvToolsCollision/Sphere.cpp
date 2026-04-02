#include "Sphere.hpp"


Sphere::Sphere(float pX, float pY, float pRadius) : Collider(pX, pY, pRadius, false) {

}
Sphere::~Sphere() {
	//dtor
}


bool Sphere::checkCollision(Collider* pCollider) const {
	if (!config::USE_DOUBLEDISPATCH) {
		return Collider::checkCollision(pCollider);
	}
	return pCollider->checkCollision((Sphere*)this);
}

bool Sphere::checkCollision(AABB* pCollider) const {

	return checkCircleAABBCollision((Collider*)pCollider);
}

bool Sphere::checkCollision(Sphere* pCollider) const {

	return checkCircleCircleCollision((Collider*)pCollider);
}