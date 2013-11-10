/*
 * Projectile.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Projectile.h"

Projectile::Projectile(float x, float y, float radius, float angle,
		float velocity, Texture* texture) :
		Entity(radius), x(x), y(y), velocity(velocity), bullet(*texture) {
	xmove = cos(angle);
	ymove = -sin(angle);

	bullet.setRotation(-angle * 180 / 3.141 + 90);
}

const Vector2f Projectile::getPosition() const {
	return Vector2f(x, y);
}

void Projectile::draw(RenderWindow* window) {
	window->draw(bullet);
}

void Projectile::move(double time) {
	x += xmove * velocity * time;
	y += ymove * velocity * time;

	bullet.setPosition(getPosition());
}
