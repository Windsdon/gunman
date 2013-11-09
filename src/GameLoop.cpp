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

	Vector2f heroPos = hero->getPosition();
	hero->rotate(atan2(mouseX - heroPos.x, mouseY - heroPos.y));

	double heroMoveSpeed= hero->getMoveSpeed();
	hero->move(heroMoveX * heroMoveSpeed * deltaTime,
			heroMoveY * heroMoveSpeed * deltaTime);

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

}

void Game::resetGame() {
	hero->setPosition(width / 2, height / 2);
}
