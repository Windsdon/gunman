/*
 * Entity.h
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AI.h"

using namespace sf;
using namespace std;

class Entity {
	public:
		Entity(double radius) : radius(radius) {};
		virtual void draw(RenderWindow*) = 0;

		bool collides(const Entity&) const;
		double getRadius() const;
		virtual const Vector2f getPosition() const = 0;

		virtual void rotate(double) = 0;
		virtual void setPosition(double, double) = 0;

		virtual const Vector2f getBulletOutputPoint() const = 0;

		virtual double getDistance(Entity*) const;
		virtual const Vector2f getPointingVector(Entity*) const;

		virtual bool isDead() const = 0;

	private:
		double radius;
};

class Mob: public Entity {
	public:
		Mob(double radius, int life, int maxLife);

		virtual int damage(int) = 0;
		virtual double getMoveSpeed() = 0;
		virtual double getAngle() const = 0;
		virtual void move(double, double) = 0;
		virtual bool isInvulnerable();
		virtual void setInvulnerable(Time);
		virtual void updateInvulnerable();
		virtual double getInvTime();
		virtual int getKnockback();
		virtual int getKnockbackResistance();
		virtual bool isDead() const;

	protected:
		int life;
		int maxLife;
		double angle;
		bool invulnerable;
		Clock invClock;
		Time invDuration;
		double invTime;
		int knockback;
		int knockbackResistance;
};

class Hero: public Mob {
	public:
		Hero(Sprite*);
		virtual void move(double, double);

		virtual void rotate(double);
		virtual const Vector2f getPosition() const;
		virtual void draw(RenderWindow*);
		virtual int damage(int);
		virtual void setPosition(double, double);
		virtual double getMoveSpeed() {return 90;}
		virtual const Vector2f getBulletOutputPoint() const;
		virtual double getAngle() const;

	private:
		Sprite *sprite;
		static const int defaultLife = 20;
		static const int size = 20;

};

class Zombie: public Mob{
	public:
		Zombie(Sprite*, int, int, int, int);

		virtual void move(double, double);

		virtual void rotate(double);
		virtual const Vector2f getPosition() const;
		virtual void draw(RenderWindow*);
		virtual int damage(int);
		virtual void setPosition(double, double);
		virtual double getMoveSpeed() {
			return 30;
		}
		virtual const Vector2f getBulletOutputPoint() const;
		virtual double getAngle() const;

		virtual void setAI(AI*);
		virtual AI* getAI();

	private:
		Sprite *sprite;
		AI* ai;


};
