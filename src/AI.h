/*
 * AI.h
 *
 *  Created on: 10/11/2013
 *      Author: Windsdon
 */

#pragma once

class Level;
class Zombie;

class AI {
	public:
		AI(Level*, Zombie*);
		virtual void tick(double) = 0;

	protected:
		Level *level;
		Zombie *creature;
};

class ClassicZombieAI: public AI {
	public:
		ClassicZombieAI(Level* level, Zombie* creature): AI(level, creature) {};
		virtual void tick(double);
};
