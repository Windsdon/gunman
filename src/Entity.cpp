/*
 * Entity.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Entity.h"
#include <iostream>
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

Hero::Hero(Sprite* sprite) :
		Mob(size, defaultLife, defaultLife), sprite(sprite) {
	sprite->setOrigin(32, 32);
	angle = 0;
	invTime = 0.5;
	knockback = 15;
	knockbackResistance = 0;
	setInvulnerable(seconds(0));
}

void Hero::move(double x, double y) {
	sprite->move(x, y);
}

void Hero::rotate(double angle) {
	this->angle = angle;
	sprite->setRotation(-angle * 180 / 3.141 + 180);
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

const Vector2f Hero::getBulletOutputPoint() const {
	return getPosition()
			+ Vector2f(getRadius() * cos(-angle + 3.141 / 2),
					getRadius() * sin(-angle + 3.141 / 2));
}

Zombie::Zombie(Sprite* sprite, int life, int size, int x, int y) :
		Mob(size, life, life), sprite(sprite), ai(NULL) {
	sprite->setOrigin(Vector2f(32, 32));
	sprite->setPosition(x, y);
	invTime = 0.1;
	knockback = 10;
	knockbackResistance = 0;
}

void Zombie::rotate(double angle) {
	this->angle = angle;
	sprite->setRotation(-angle * 180 / 3.141 + 180);
}

const Vector2f Zombie::getPosition() const {
	return sprite->getPosition();
}

void Zombie::draw(RenderWindow* window) {
	window->draw(*sprite);
}

int Zombie::damage(int damage) {
	life -= damage;
	return damage;
}

void Zombie::setPosition(double x, double y) {
	sprite->setPosition(x, y);
}

const Vector2f Zombie::getBulletOutputPoint() const {
	return sprite->getPosition();
}

void Zombie::setAI(AI* ai) {
	this->ai = ai;
}

double Zombie::getAngle() const {
	return angle;
}

AI* Zombie::getAI() {
	return ai;
}

double Hero::getAngle() const {
	return angle;
}

double Entity::getDistance(Entity* other) const {
	Vector2f thisPos = getPosition();
	Vector2f otherPos = other->getPosition();
	return sqrt(pow(thisPos.x - otherPos.x, 2) + pow(thisPos.y - otherPos.y, 2));
}

const Vector2f Entity::getPointingVector(Entity* other) const {
	double distance = getDistance(other);
	Vector2f thisPos = getPosition();
	Vector2f otherPos = other->getPosition();

	return Vector2f((otherPos.x - thisPos.x) / distance,
			(otherPos.y - thisPos.y) / distance);
}

void Zombie::move(double x, double y) {
	sprite->move(x, y);
}

bool Mob::isInvulnerable() {
	return invulnerable;
}

void Mob::setInvulnerable(Time duration) {
	invClock.restart();
	invDuration = duration;
}

void Mob::updateInvulnerable() {
	invulnerable = ((invDuration - invClock.getElapsedTime()).asSeconds() > 0);
	//cout << "Hero is inv? " << ((invDuration - invClock.getElapsedTime()).asSeconds() > 0) << endl;
}

double Mob::getInvTime() {
	return invTime;
}

int Mob::getKnockback() {
	return knockback;
}

int Mob::getKnockbackResistance() {
	return knockbackResistance;
}

bool Mob::isDead() const {
	return life <= 0;
}
