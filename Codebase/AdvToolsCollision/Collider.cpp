#include "Collider.hpp"

Collider::Collider(float pX, float pY, float pRadius, bool pAabb) : GameObject("Collider", glm::vec3(pX, 0, pY)), radius(pRadius), isAABB(pAabb), prev_(NULL), next_(NULL), cellX(0), cellY(0), gridNr(0), isColliding(false) {

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


	glm::vec2 diff = pCollider->GetVec2Pos() - GetVec2Pos();
	float centerDist = sqrt(diff.x * diff.x + diff.y * diff.y);

	float edgeDist = centerDist - pCollider->getRadius() - getRadius();
	return edgeDist <= 0 ? true : false;

}

bool Collider::checkCircleAABBCollision(Collider* pCollider) const {


	glm::vec2 cPos = GetVec2Pos();

	glm::vec2 aPos = pCollider->GetVec2Pos();

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


	glm::vec2 aPos = GetVec2Pos();


	glm::vec2 cPos = pCollider->GetVec2Pos();

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

	glm::vec2 pos1 = GetVec2Pos();
	glm::vec2 pos2 = pCollider->GetVec2Pos();

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

void Collider::SetColMaterial(float r, float g, float b, float a) {
	((ColorMaterial*)getMaterial())->setDiffuseColor(glm::vec4(r, g, b, a));
}

void Collider::ReloadMaterial() {
	float r = (isColliding) ? 1.0f : 0;
	float g = (float)cellX / (config::GRID_CELL_COUNT - 1);
	float b = (float)cellY / (config::GRID_CELL_COUNT - 1);
	float a = ((float)gridNr + 1) / 10;
	SetColMaterial(r, g, b, a);
	//((ColorMaterial*)getMaterial())->setDiffuseColor(glm::vec4(r, g, b, a));
}

glm::vec2 Collider::GetVec2Pos() const {
	return ((MoveBehaviour*)getBehaviour())->GetPosition();
}