/*
 * Entity.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Entity.h"
#include <math.h>

bool Entity::collides(const Entity& other) const {
	Vector2f pos1 = getPosition();
	Vector2f pos2 = other.getPosition();

	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2))
			<= (getRadius() + other.getRadius());
}

double Entity::getRadius() const {
	return radius;
}

Mob::Mob(double radius, int life, int maxLife) :
		Entity(radius), life(life), maxLife(life) {
}

Hero::Hero(Sprite* sprite): Mob(size, defaultLife, defaultLife), sprite(sprite) {
	sprite->setOrigin(34, 44);
}

void Hero::tick(){
	//TODO
}

void Hero::move(double x, double y) {
	sprite->move(x, y);
}

void Hero::rotate(double angle){
	sprite->setRotation(-angle * 180/3.141 + 180);
}

const Vector2f Hero::getPosition() const {
	return sprite->getPosition();
}

void Hero::draw(RenderWindow* window) {
	window->draw(*sprite);
}

int Hero::damage(int damage) {
	life -= damage;
	return damage;
}

void Hero::setPosition(double x, double y) {
	sprite->setPosition(x, y);
}
