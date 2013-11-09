/*
 * Game.h
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "MainMenu.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class Game {
	public:
		Game();
		int onStart();

	private:
		bool onLoad();
		void loop();
		void onEvent();
		void onUpdate();
		void onRender();
		void onClose();

		void drawMainMenu();
		void drawScene();

		void resetGame();

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

		Hero *hero;

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

		Texture *heroTexture;

		/*
		 * SPRITES
		 */
		Sprite *splashSprite;
		Sprite *logoSprite;
		Sprite *menuBGSprite;
		Sprite *ambientSprite;

		Sprite *heroSprite;

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

		/*
		 * THREADS
		 */
		Thread *renderThread;

		/*
		 * MENUS
		 */
		MainMenu *mainMenu;
};
