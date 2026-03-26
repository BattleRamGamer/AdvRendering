#include "Collider.hpp"

Collider::Collider(float radius, bool aabb) : GameObject("Collider"), radius(radius), isAABB(aabb) {

}

Collider::~Collider() {

}

bool Collider::checkCollision(Collider* pCollider) const {

	if (getIsAABB()) {
		if (pCollider->getIsAABB()) {
			return checkAABBAABBCollision(pCollider);
		}
		return checkAABBCircleCollision(pCollider);
	}
	if (pCollider->getIsAABB()) {
		return checkCircleAABBCollision(pCollider);
	}
	return checkCircleCircleCollision(pCollider);

}

bool Collider::checkCircleCircleCollision(Collider* pCollider) const {

	glm::vec3 diff = pCollider->getWorldPosition() - getWorldPosition();
	float centerDist = sqrt(diff.x * diff.x + diff.z * diff.z);
	float edgeDist = centerDist - pCollider->getRadius() - getRadius();
	return edgeDist <= 0 ? true : false;

}

bool Collider::checkCircleAABBCollision(Collider* pCollider) const {

	glm::vec3 cPos3 = getWorldPosition();
	glm::vec2 cPos = glm::vec2(cPos3.x, cPos3.z);

	glm::vec3 aPos3 = pCollider->getWorldPosition();
	glm::vec2 aPos = glm::vec2(aPos3.x, aPos3.z);

	glm::vec2 diff = aPos - cPos;

	glm::vec2 dir = diff / sqrt(diff.x * diff.x + diff.y * diff.y);

	glm::vec2 cPosNearest = cPos + dir * getRadius();

	if (cPosNearest.x >= aPos.x - pCollider->getRadius() &&
		cPosNearest.x <= aPos.x + pCollider->getRadius() &&
		cPosNearest.y >= aPos.y - pCollider->getRadius() &&
		cPosNearest.y <= aPos.y + pCollider->getRadius() ) 
	{
		return true;
	}
	return false;

}

bool Collider::checkAABBCircleCollision(Collider* pCollider) const {

	glm::vec3 aPos3 = getWorldPosition();
	glm::vec2 aPos = glm::vec2(aPos3.x, aPos3.z);

	glm::vec3 cPos3 = pCollider->getWorldPosition();
	glm::vec2 cPos = glm::vec2(cPos3.x, cPos3.z);

	glm::vec2 diff = aPos - cPos;

	glm::vec2 dir = diff / sqrt(diff.x * diff.x + diff.y * diff.y);

	glm::vec2 cPosNearest = cPos + dir * pCollider->getRadius();

	if (cPosNearest.x >= aPos.x - getRadius()  &&
		cPosNearest.x <= aPos.x + getRadius()  &&
		cPosNearest.y >= aPos.y - getRadius()  &&
		cPosNearest.y <= aPos.y + getRadius() )
	{
		return true;
	}
	return false;

}

bool Collider::checkAABBAABBCollision(Collider* pCollider) const {

	glm::vec3 threePos1 = getWorldPosition();
	glm::vec3 threePos2 = pCollider->getWorldPosition();

	glm::vec2 pos1 = glm::vec2(threePos1.x, threePos1.z);
	glm::vec2 pos2 = glm::vec2(threePos2.x, threePos2.z);

	float rad1 = getRadius();
	float rad2 = pCollider->getRadius();

	if (pos1.x + rad1 >= pos2.x - rad2 &&
		pos1.x - rad1 <= pos2.x + rad2 &&
		pos1.y + rad1 >= pos2.y - rad2 &&
		pos1.y - rad1 <= pos2.y + rad2) 
	{
		return true;
	}
	return false;

}

bool Collider::checkCollision(AABB* pCollider) const {
	if (getIsAABB()) {
		return checkAABBAABBCollision((Collider*)pCollider);
	}
	return checkCircleAABBCollision((Collider*)pCollider);
}

bool Collider::checkCollision(Sphere* pCollider) const {
	if (getIsAABB()) {
		return checkAABBCircleCollision((Collider*)pCollider);
	}
	return checkCircleCircleCollision((Collider*)pCollider);
}

float Collider::getRadius() const {
	return radius;
}

bool Collider::getIsAABB() const {
	return isAABB;
}