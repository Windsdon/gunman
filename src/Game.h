/*
 * Game.h
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "MainMenu.h"
#include "Entity.h"
#include "Projectile.h"
#include "Level.h"

using namespace sf;
using namespace std;

class Game {
	friend class Level;
	public:
		Game();
		int onStart();

	private:
		bool onLoad();
		void loop();
		void onUpdate();
		void onRender();

		void drawMainMenu();
		void drawScene();

		void resetGame();

		bool loadSound(Sound**, SoundBuffer**, const string&);

		static const int width = 1280;
		static const int height = 720;

		enum GameState {
			Stopped,
			Splash,
			Menu,
			Playing,
			Paused,
			Death,
			Switching
		};

		/*
		 * GAME VARIABLES
		 */
		GameState gameState;

		Level *level;

		int mouseX, mouseY;

		/*
		 * UTILITIES
		 */

		bool loadTexture(Texture*, const string&);
		bool loadSprite(Sprite**, Texture**, const string&);

		/*
		 * WINDOWS
		 */
		RenderWindow *splash;
		RenderWindow *window;

		VideoMode mode;
		ContextSettings ctx;

		/*
		 * TEXTURES
		 */
		Texture *splashTexture;
		Texture *logoTexture;
		Texture *menuBGTexture;
		Texture *ambientTexture;

		Texture *bulletTexture;

		Texture *heroTexture;
		Texture *zombieTexture;

		/*
		 * SPRITES
		 */
		Sprite *splashSprite;
		Sprite *logoSprite;
		Sprite *menuBGSprite;
		Sprite *ambientSprite;

		Sprite *heroSprite;

		/*
		 * SOUNDS
		 */
		SoundBuffer *hitBuffer1;
		Sound *hitSound1;

		SoundBuffer *shootBuffer1;
		Sound *shootSound1;

		SoundBuffer *explosionBuffer1;
		Sound *explosionSound1;

		/*
		 * FONTS
		 */

		Font *menuFont;

		/*
		 * TIMERS
		 */
		Clock splashTimer;
		Time splashMin;
		Clock tickTimer;
		Clock shootTimer;
		Time shootInterval;

		/*
		 * THREADS
		 */
		Thread *renderThread;

		/*
		 * MENUS
		 */
		MainMenu *mainMenu;
};
