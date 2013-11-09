/*
 * MainMenu.cpp
 *
 *  Created on: 09/11/2013
 *      Author: Windsdon
 */

#include "MainMenu.h"
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

MainMenu::MainMenu(Font &font) {
	selectedIndex = 0;

	createItem(0, "Play", Option::Play, font, size, Vector2f(300, 50));
	createItem(1, "Exit", Option::Exit, font, size, Vector2f(300, 50));

	selected = false;
}

void MainMenu::draw(RenderWindow* window) {
	for(int i = 0; i < optionCount; i++){
		if(selectedIndex == i){
			window->draw(options[i]->background);
		}
		window->draw(options[i]->textObj);
	}
}

void MainMenu::event(Event& e) {
	if(e.type == Event::KeyPressed){
		if(e.key.code == Keyboard::Up || e.key.code == Keyboard::W){
			selectedIndex = abs((--selectedIndex)%optionCount);
		}else if(e.key.code == Keyboard::Down || e.key.code == Keyboard::S){
			selectedIndex = abs((++selectedIndex)%optionCount);
		}
	}
}

void MainMenu::createItem(int index, const string text, MainMenu::Option id,
		const Font &font, int size, Vector2f bgsize) {
	MenuOption *option = new MenuOption(text, id, font, size, bgsize);

	int adjust = -12;
	option->background.setFillColor(Color(7, 15, 20));
	option->background.setOrigin(Vector2f(150, 0));
	option->background.setPosition(640, 400 + index * (55));
	option->textObj.setColor(Color::White);
	FloatRect textSize = options[0]->textObj.getLocalBounds();
	option->textObj.setOrigin(textSize.width / 2, textSize.height / 2);
	option->textObj.setPosition(640, 425 + index * (55) + adjust);

	options[index] = option;
}

MainMenu::Option MainMenu::getSelectedOption() {
	return (selected) ? options[selectedIndex]->option : Option::None;
}
