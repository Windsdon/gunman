/*
 * Level.h
 *
 *  Created on: 10/11/2013
 *      Author: Windsdon
 */

#pragma once

#include "Entity.h"
#include "Projectile.h"
#include <vector>

using namespace std;
class Game;

class Level {
	public:
		Level(Hero*, Game*);

		void addEnemy(Zombie*);
		void killEnemy(Zombie*);
		void killProjectile(Projectile*);

		void fireProjectile(int, const Vector2f&, double);

		void tick(double);

		Hero *getHero();
		vector<Zombie*> &getEnemies();
		vector<Projectile*> &getProjectiles();

	private:
		vector<Zombie*> enemies;
		vector<Projectile*> projectiles;
		Hero* hero;
		Game* game;
};

