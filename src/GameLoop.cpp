/*
 * GameLoop.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Game.h"
#include <iostream>

void Game::loop(){
	//updateThread = new Thread(&Game::onUpdate, this);
	renderThread = new Thread(&Game::onRender, this);

	//updateThread->launch();
	renderThread->launch();

	gameState = GameState::Menu;

	while(gameState != GameState::Stopped){
		onUpdate();
	}

	//updateThread->wait();
	//renderThread->terminate();
}

void Game::onUpdate(){
	Event e;
	while (window->pollEvent(e)) {
		if(gameState == GameState::Menu){
			mainMenu->event(e);
		}
		if (e.type == Event::Closed) {
			gameState = GameState::Stopped;
		}
	}

}
