#ifndef AABB_HPP
#define AABB_HPP


#include "mge/core/GameObject.hpp"
#include "Collider.hpp"

class AABB : public Collider
{
public:

	AABB(float pRadius);
	~AABB();

	virtual bool checkCollision(AABB* pCollider) const;
	virtual bool checkCollision(Sphere* pCollider) const;

	virtual bool checkCollision(Collider* pCollider) const;

protected:

private:

};


#endif // AABB_HPP