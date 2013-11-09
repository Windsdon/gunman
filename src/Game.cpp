/*
 * Game.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(): mode(1280, 720, 32) {
	cout << "Creating instance " << endl;
	ctx.antialiasingLevel = 8;
	splash = new RenderWindow(mode, "GunMan", Style::None, ctx);
	gameState = GameState::Splash;

}

//loads everything
int Game::onStart() {

	splashTexture = new Texture();
	if(!loadTexture(splashTexture, "res/splash.png")){
		return 1;
	}

	splashSprite = new Sprite(*splashTexture);

	splashMin = seconds(1);
	splashTimer.restart();

	splash->clear();
	splash->draw(*splashSprite);
	splash->display();

	if(!onLoad()){
		return 1;
	}

	while(splashTimer.getElapsedTime() < splashMin); // :P who cares?

	splash->close();
	delete splash;

	window = new RenderWindow(mode, "GunMan", Style::Close, ctx);
	window->setActive(false);

	loop();

	return 0;
}

bool Game::onLoad() {
	if(!loadSprite(&logoSprite, &logoTexture, "res/logo.png")){
		return false;
	}
	Vector2u logoSize = logoTexture->getSize();
	logoSprite->setOrigin(logoSize.x/2, 0);
	logoSprite->setPosition(width/2, 10);

	if(!loadSprite(&menuBGSprite, &menuBGTexture, "res/menu_bg.png")){
		return false;
	}

	if(!loadSprite(&ambientSprite, &ambientTexture, "res/ambient.png")){
		return false;
	}

	menuFont = new Font();
	if(!menuFont->loadFromFile("res/masterplan.ttf")){
		cout << "[SEVERE] Failed to open font" << endl;
		return false;
	}else{
		cout << "[INFO] Loaded font" << endl;
	}

	if(!loadSprite(&heroSprite, &heroTexture, "res/zombie1.png")){
		return false;
	}

	hero = new Hero(heroSprite);

	mainMenu = new MainMenu(*menuFont);

	return true;
}

bool Game::loadTexture(Texture* texture, const string& name) {
	if(!texture->loadFromFile(name)){
		cout << "[SEVERE] failed to load texture: " << name << endl;
		return false;
	}else{
		cout << "[INFO] Texture loaded: " << name << endl;
	}

	return true;
}

bool Game::loadSprite(Sprite** sprite, Texture** texture, const string& name) {
	*texture = new Texture();
	if(!loadTexture(*texture, name)){
		return false;
	}
	*sprite = new Sprite(**texture);

	return true;
}
