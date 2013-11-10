/*
 * Level.cpp
 *
 *  Created on: 10/11/2013
 *      Author: Windsdon
 */

#include "Level.h"
#include "Game.h"
#include <iostream>

Level::Level(Hero* hero, Game* game) :
		hero(hero), game(game) {
}

void Level::addEnemy(Zombie* enemy) {
	enemies.push_back(enemy);
}

void Level::killEnemy(Zombie* enemy) {
	for (vector<Zombie*>::iterator it = enemies.begin(); it != enemies.end();) {
		if (*it == enemy) {
			enemies.erase(it);
			//TODO delete enemy;
		}else{
			++it;
		}
	}
}

void Level::killProjectile(Projectile* projectile) {
	for (vector<Projectile*>::iterator it = projectiles.begin();
			it != projectiles.end();) {
		if (*it == projectile) {
			projectiles.erase(it);
			//TODO delete projectile;
		} else {
			++it;
		}
	}
}

void Level::fireProjectile(int type, const Vector2f& position, double angle) {
	Texture* bulletTexture = game->bulletTexture;
	projectiles.push_back(
			new Projectile(position.x, position.y, 1, angle - 90 * 3.141 / 180,
					2400, bulletTexture));
	game->shootSound1->play();

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
	hero->updateInvulnerable();

	for(unsigned int i = 0; i < projectiles.size(); i++){
		Projectile *projectile = projectiles[i];
		projectile->move(deltaTime);
		for(unsigned int j = 0; j < enemies.size(); j++){
			Zombie *enemy = enemies[j];
			if(projectile->collides(*enemy) && !enemy->isInvulnerable()){
				enemy->damage(projectile->getDamage());
				game->hitSound1->play();

				projectile->pierced(1);
				if(projectile->isDead()){
					killProjectile(projectiles[i]);
				}

				enemy->setInvulnerable(seconds(enemy->getInvTime()));
				if(enemy->isDead()){
					game->explosionSound1->play();
					killEnemy(enemy);
				}
			}
		}
	}

	for (vector<Zombie*>::iterator enemy = enemies.begin();
			enemy != enemies.end(); ++enemy) {
		(*enemy)->getAI()->tick(deltaTime);
		Zombie *thisEnemy = *enemy;
		thisEnemy->updateInvulnerable();
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

		if (!hero->isInvulnerable()) {
			if (thisEnemy->collides(*hero)) {
				cout << "Hit" << endl;
				hero->damage(1);
				hero->setInvulnerable(seconds(hero->getInvTime()));
				Vector2f hitVec = thisEnemy->getPointingVector(hero);
				int knockback = thisEnemy->getKnockback()
						- hero->getKnockbackResistance()
						+ thisEnemy->getDistance(hero);
				hero->move(knockback * hitVec.x, knockback * hitVec.y);
			}
		}
	}
}

void Level::spawnZombie() {
	Zombie *zombie = new Zombie(new Sprite(*(game->zombieTexture)), 10, 22, 0,
			0);
	ClassicZombieAI *ai = new ClassicZombieAI(this, zombie);

	zombie->setAI(ai);
	addEnemy(zombie);
}
