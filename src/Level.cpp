/*
 * Level.cpp
 *
 *  Created on: 10/11/2013
 *      Author: Windsdon
 */

#include "Level.h"
#include "Game.h"

Level::Level(Hero* hero, Game* game) :
		hero(hero), game(game) {
}

void Level::addEnemy(Zombie* enemy) {
	enemies.push_back(enemy);
}

void Level::killEnemy(Zombie* enemy) {
	for (vector<Zombie*>::iterator it = enemies.begin(); it != enemies.end();
			++it) {
		if (*it == enemy) {
			enemies.erase(it);
			delete enemy;
		}
	}
}

void Level::killProjectile(Projectile* projectile) {
	for (vector<Projectile*>::iterator it = projectiles.begin();
			it != projectiles.end(); ++it) {
		if (*it == projectile) {
			projectiles.erase(it);
			delete projectile;
		}
	}
}

void Level::fireProjectile(int type, const Vector2f& position, double angle) {
	Texture* bulletTexture = game->bulletTexture;
	projectiles.push_back(
			new Projectile(position.x, position.y, 3, angle - 90 * 3.141 / 180,
					2400, bulletTexture));
}

Hero* Level::getHero() {
	return hero;
}

vector<Zombie*>& Level::getEnemies() {
	return enemies;
}

vector<Projectile*>& Level::getProjectiles() {
	return projectiles;
}

void Level::tick(double deltaTime) {
	for (vector<Projectile*>::iterator projectile = projectiles.begin();
			projectile != projectiles.end(); ++projectile) {
		(*projectile)->move(deltaTime);
	}

	for (vector<Zombie*>::iterator enemy = enemies.begin();
			enemy != enemies.end(); ++enemy) {
		(*enemy)->getAI()->tick(deltaTime);
		Zombie *thisEnemy = *enemy;
		for (vector<Zombie*>::iterator enemy2 = enemies.begin();
				enemy2 != enemies.end(); ++enemy2) {
			if (enemy2 == enemy) {
				continue;
			}
			Zombie *otherEnemy = *enemy2;
			double distance = thisEnemy->getDistance(otherEnemy);
			double thisRadius = thisEnemy->getRadius();
			double otherRadius = otherEnemy->getRadius();

			if (distance < thisRadius + otherRadius) {
				Vector2f vecMove = thisEnemy->getPointingVector(otherEnemy);
				double moveIntensity = (distance - thisRadius - otherRadius);
				thisEnemy->move(moveIntensity * vecMove.x,
						moveIntensity * vecMove.y);
			}
		}
	}
}

void Level::spawnZombie() {
	Zombie *zombie = new Zombie(new Sprite(*(game->zombieTexture)), 1, 30, 0,
			0);
	ClassicZombieAI *ai = new ClassicZombieAI(this, zombie);

	zombie->setAI(ai);
	addEnemy(zombie);
}
