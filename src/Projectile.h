/*
 * Projectile.h
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#pragma once

#include "Entity.h"

class Projectile: public Entity {
	public:
		Projectile(float x, float y, float radius, float angle, float velocity, Texture *texture);

		virtual const Vector2f getPosition() const;

		virtual void draw(RenderWindow*);

		virtual void rotate(double) {};
		virtual void setPosition(double, double){};
		virtual void move(double);

		virtual const Vector2f getBulletOutputPoint() const {return Vector2f();};

		enum Type {
			Bullet
		};

	private:
		float x;
		float y;
		float xmove;
		float ymove;
		float velocity;

		Sprite bullet;
};
