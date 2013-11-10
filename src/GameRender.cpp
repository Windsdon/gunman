/*
 * GameRender.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */
#include "Game.h"
#include <iostream>

void Game::onRender() {
	window->setActive(true); //activate on this thread
	//window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	RenderStates rs;
	while (gameState != GameState::Stopped) {
		if(gameState == GameState::Switching){
			continue;
		}
		window->clear();
		switch (gameState) {
			case GameState::Menu:
				drawMainMenu();
				break;
			case GameState::Playing:
			case GameState::Paused:
			case GameState::Death:
				drawScene();
				break;
		}
		window->display();
	}
}

void Game::drawMainMenu() {
	window->draw(*menuBGSprite);
	window->draw(*logoSprite);
	mainMenu->draw(window);
}

void Game::drawScene(){
	window->draw(*ambientSprite);

	for(vector<Projectile*>::iterator t = level->getProjectiles().begin(); t != level->getProjectiles().end(); ++t){
		(*t)->draw(window);
	}

	level->getHero()->draw(window);
}
