/*
 * AI.cpp
 *
 *  Created on: 10/11/2013
 *      Author: Windsdon
 */

#include "AI.h"
#include "Entity.h"
#include "Level.h"
#include <iostream>
#include <stdio.h>

AI::AI(Level* level, Zombie* creature): level(level), creature(creature) {

}

void ClassicZombieAI::tick(double time) {

	Hero *hero = level->getHero();
	Vector2f pointing = creature->getPointingVector(hero);

	double moveAmmount = time * creature->getMoveSpeed();
	double xmove = pointing.x * moveAmmount;
	double ymove = pointing.y * moveAmmount;

	creature->move(xmove, ymove);
	creature->rotate(atan2(xmove, ymove));
}
