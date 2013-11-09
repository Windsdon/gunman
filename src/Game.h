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

		static const int width = 1280;
		static const int height = 720;

		enum GameState {
			Stopped,
			Splash,
			Menu,
			Playing,
			Paused,
			Death
		};

		/*
		 * GAME VARIABLES
		 */
		GameState gameState;

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

		/*
		 * STAND-ALONE SPRITES
		 */
		Sprite *splashSprite;
		Sprite *logoSprite;
		Sprite *menuBGSprite;

		/*
		 * FONTS
		 */

		Font *menuFont;

		/*
		 * TIMERS
		 */
		Clock splashTimer;
		Time splashMin;

		/*
		 * THREADS
		 */
		Thread *renderThread;

		/*
		 * MENUS
		 */
		MainMenu *mainMenu;
};
