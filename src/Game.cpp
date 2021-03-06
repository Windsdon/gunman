/*
 * Game.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() :
		mode(1280, 720, 32) {
	cout << "Creating instance " << endl;
	ctx.antialiasingLevel = 8;
	splash = new RenderWindow(mode, "GunMan", Style::None, ctx);
	gameState = GameState::Splash;

}

//loads everything
int Game::onStart() {

	splashTexture = new Texture();
	if (!loadTexture(splashTexture, "res/splash.png")) {
		return 1;
	}

	splashSprite = new Sprite(*splashTexture);

	splashMin = seconds(1);
	splashTimer.restart();

	splash->clear();
	splash->draw(*splashSprite);
	splash->display();

	if (!onLoad()) {
		return 1;
	}

	while (splashTimer.getElapsedTime() < splashMin)
		; // :P who cares?

	splash->close();
	delete splash;

	window = new RenderWindow(mode, "GunMan", Style::Close, ctx);
	window->setActive(false);

	loop();

	return 0;
}

bool Game::onLoad() {
	if (!loadSprite(&logoSprite, &logoTexture, "res/logo.png")) {
		return false;
	}
	Vector2u logoSize = logoTexture->getSize();
	logoSprite->setOrigin(logoSize.x / 2, 0);
	logoSprite->setPosition(width / 2, 10);

	if (!loadSprite(&menuBGSprite, &menuBGTexture, "res/menu_bg.png")) {
		return false;
	}

	if (!loadSprite(&ambientSprite, &ambientTexture, "res/ambient.png")) {
		return false;
	}

	menuFont = new Font();
	if (!menuFont->loadFromFile("res/masterplan.ttf")) {
		cout << "[SEVERE] Failed to open font" << endl;
		return false;
	} else {
		cout << "[INFO] Loaded font" << endl;
	}

	if (!loadSprite(&heroSprite, &heroTexture, "res/hero2.png")) {
		return false;
	}

	bulletTexture = new Texture();
	if (!loadTexture(bulletTexture, "res/bullet.png")) {
		return false;
	}

	zombieTexture = new Texture();
	if(!loadTexture(zombieTexture, "res/zombie1.png")){
		return false;
	}

	if(!loadSound(&hitSound1, &hitBuffer1, "res/hit1.wav")){
		return false;
	}

	if(!loadSound(&shootSound1, &shootBuffer1, "res/shoot1.wav")){
		return false;
	}

	if(!loadSound(&explosionSound1, &explosionBuffer1, "res/explode1.wav")){
		return false;
	}

	level = new Level(new Hero(heroSprite), this);

	mainMenu = new MainMenu(*menuFont);

	return true;
}

bool Game::loadTexture(Texture* texture, const string& name) {
	if (!texture->loadFromFile(name)) {
		cout << "[SEVERE] failed to load texture: " << name << endl;
		return false;
	} else {
		cout << "[INFO] Texture loaded: " << name << endl;
	}

	return true;
}

bool Game::loadSound(Sound** sound, SoundBuffer** buffer, const string &path) {
	*buffer = new SoundBuffer();
	if(!(*buffer)->loadFromFile(path)){
		cout << "[SEVERE] Failed to load sound " << path << endl;
		return false;
	}else{
		cout << "[INFO] Loaded sound " << path << endl;
	}

	*sound = new Sound(**buffer);
	(*sound)->setLoop(false);

	return true;
}

bool Game::loadSprite(Sprite** sprite, Texture** texture, const string& name) {
	*texture = new Texture();
	if (!loadTexture(*texture, name)) {
		return false;
	}
	*sprite = new Sprite(**texture);

	return true;
}
