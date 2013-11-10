/*
 * GameLoop.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Game.h"
#include <iostream>

void Game::loop() {
	//updateThread = new Thread(&Game::onUpdate, this);
	renderThread = new Thread(&Game::onRender, this);

	//updateThread->launch();
	renderThread->launch();

	gameState = GameState::Menu;

	while (gameState != GameState::Stopped) {
		onUpdate();
	}

	//updateThread->wait();
	//renderThread->terminate();
}

void Game::onUpdate() {
	Event e;
	//bool shootScheduled = false;
	bool spawn = false;

	while (window->pollEvent(e)) {
		if (gameState == GameState::Menu) {
			mainMenu->event(e);
		}
		if (e.type == Event::Closed) {
			gameState = GameState::Stopped;
		}
		if (e.type == Event::MouseMoved) {
			mouseX = e.mouseMove.x;
			mouseY = e.mouseMove.y;
		}
//		if (e.type == Event::MouseButtonPressed) {
//			shootScheduled = true;
//		}

		if (e.type == Event::MouseButtonPressed) {
			if (e.mouseButton.button == Mouse::Right) {
				spawn = true;
			}
		}
	}

	if (gameState == GameState::Menu) {
		switch (mainMenu->getSelectedOption()) {
		case MainMenu::Option::Exit:
			gameState = GameState::Stopped;
			break;
		case MainMenu::Option::Play:
			resetGame();
			gameState = GameState::Playing;
			break;
		}
	}

	if (gameState != GameState::Playing) {
		return;
	}

	float heroMoveX = 0, heroMoveY = 0;

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		heroMoveX++;
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		heroMoveX--;
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		heroMoveY--;
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		heroMoveY++;
	}

	Time delta = tickTimer.restart();
	double deltaTime = delta.asSeconds();

	Hero *hero = level->getHero();

	Vector2f heroPos = hero->getPosition();
	double heroAngle = atan2(mouseX - heroPos.x, mouseY - heroPos.y);

	hero->rotate(heroAngle);

	double heroMoveSpeed = hero->getMoveSpeed();

	hero->move(heroMoveX * heroMoveSpeed * deltaTime,
			heroMoveY * heroMoveSpeed * deltaTime);

	if (Mouse::isButtonPressed(Mouse::Left)
			&& shootTimer.getElapsedTime() >= shootInterval) {
		shootTimer.restart();
		level->fireProjectile(Projectile::Type::Bullet,
				hero->getBulletOutputPoint(), heroAngle);
	}

	if (spawn) {
		cout << "Spawning zombie" << endl;
		level->spawnZombie();
	}

	level->tick(deltaTime); //move zombies, projectiles and updates explosions

}

void Game::resetGame() {
	level->getHero()->setPosition(width / 2, height / 2);
	shootInterval = seconds(0.1);
}
