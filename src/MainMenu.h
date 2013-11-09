/*
 * MainMenu.h
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class MainMenu {
	public:
		MainMenu(Font&);

		void draw(RenderWindow *window);
		void event(Event &e);

		enum Option {
			None, Play, Exit
		};

		Option getSelectedOption();

	private:
		struct MenuOption {
			public:
				MenuOption(const string text, Option id, const Font &font, unsigned int size, Vector2f &bgsize) :
						text(text), option(id), textObj(text, font, size), background(bgsize) {
				}
				const string text;
				Option option;
				Text textObj;
				RectangleShape background;
		};

		void createItem(int index, const string text, MainMenu::Option id, const Font &font, int size, Vector2f bgsize);

		MenuOption* options[2];
		int selectedIndex;
		bool selected;
		static const int optionCount = 2;
		static const int size = 42;

};
