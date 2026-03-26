#ifndef SPHERE_HPP
#define SPHERE_HPP


#include "mge/core/GameObject.hpp"
#include "Collider.hpp"

class Sphere : public Collider
{
public:

	Sphere(float pRadius);
	~Sphere();

	virtual bool checkCollision(AABB* pCollider) const;
	virtual bool checkCollision(Sphere* pCollider) const;

	virtual bool checkCollision(Collider* pCollider) const;

protected:

private:

};


#endif // SPHERE_HPP