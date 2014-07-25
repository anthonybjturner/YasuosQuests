#include "../headers/stdafx.h"
#include "../headers/FocusedAttributesWindow.h"
#include <iostream>
#include <iomanip>
#include <sstream>

FocusedAttributesWindow::FocusedAttributesWindow() :MessageWindow(){

	entity_type.setString("");
	entity_type.setFont(getFont());
	entity_type.setCharacterSize(4);

	health_text.setString("");
	health_text.setFont(getFont());
	health_text.setCharacterSize(4);

	mana_text.setString("");
	mana_text.setFont(getFont());
	mana_text.setCharacterSize(4);

	charge_text.setString("");
	charge_text.setFont(getFont());
	charge_text.setCharacterSize(4);

	coords_text.setPosition(charge_text.getPosition().x + 64, 0);

}


FocusedAttributesWindow::FocusedAttributesWindow(int x, int y, int width, int height, int size) :MessageWindow(x, y, width, height, size){

	sf::Font& font = getFont();
	unsigned int font_size = 16;

	entity_type.setString( "" );
	entity_type.setFont(font);
	entity_type.setCharacterSize(font_size);

	health_text.setString("" );
	health_text.setFont(font);
	health_text.setCharacterSize(font_size);
	health_text.setColor(sf::Color::Green);

	mana_text.setString( "" );
	mana_text.setFont(font);
	mana_text.setCharacterSize(font_size);
	mana_text.setColor(sf::Color::Green);

	charge_text.setString( "" );
	charge_text.setFont(font);
	charge_text.setCharacterSize(font_size);
	charge_text.setColor(sf::Color::Green);


	level_txt.setString("");
	level_txt.setFont(font);
	level_txt.setCharacterSize(font_size);
	level_txt.setColor(sf::Color::Green);


	exp_text.setString("");
	exp_text.setFont(font);
	exp_text.setCharacterSize(font_size);
	exp_text.setColor(sf::Color::Green);

	coords_text.setString("");
	coords_text.setFont(font);
	coords_text.setCharacterSize(font_size);
	coords_text.setColor(sf::Color::Green);

	entity_type.setPosition((float)x, (float)y);
	
	level_txt.setPosition(entity_type.getPosition().x + 64, y);
	exp_text.setPosition(level_txt.getPosition().x, level_txt.getPosition().y + 16);
	
	health_text.setPosition(level_txt.getPosition().x + 64, y);
	mana_text.setPosition(health_text.getPosition().x, health_text.getPosition().y + 16);
	
	charge_text.setPosition(mana_text.getPosition().x + 64, y);
	coords_text.setPosition(charge_text.getPosition().x, y + 16);
}



FocusedAttributesWindow::~FocusedAttributesWindow()
{
}


void FocusedAttributesWindow::draw(sf::RenderWindow* window){

	//window->draw(message_window_background);
	//window->draw(message_window_pic);
	drawEntityText(window);
	drawEntityHealthText(window);
	drawEntityManaText(window);
	drawEntityChargeText(window);
	drawEntityLevelText(window);
	drawEntityCoordinatesText(window);
	drawEntityChargeText(window);
	drawEntityXp(window);
}

void FocusedAttributesWindow::drawEntityText(sf::RenderWindow* window){

	window->draw(entity_type );

}
void FocusedAttributesWindow::drawEntityHealthText(sf::RenderWindow* window){

	window->draw(health_text);

}

void FocusedAttributesWindow::drawEntityManaText(sf::RenderWindow* window){

	window->draw(mana_text);

}

void FocusedAttributesWindow::drawEntityChargeText(sf::RenderWindow* window){
	window->draw(charge_text);


}

void FocusedAttributesWindow::drawEntityXp(sf::RenderWindow* window){

	window->draw(exp_text);

}

void FocusedAttributesWindow::drawEntityLevelText(sf::RenderWindow* window){
	window->draw(level_txt);
}


void FocusedAttributesWindow::drawEntityCoordinatesText(sf::RenderWindow* window){

	window->draw(coords_text);

}


void FocusedAttributesWindow::setEntityTypeText(std::string value){


	entity_type.setString(value);
}

void FocusedAttributesWindow::setHealthText(int value, float max_value){

	sf::Color health_color = sf::Color::Green;
	if (value >= 0 && (value/max_value) <= 0.2f){

		health_color = sf::Color::Red;

	}
	else if (value/max_value <= 0.4f){

		health_color = sf::Color::Yellow;

	}

	health_text.setColor(health_color);
	health_text.setString("HP " + std::to_string(value));


}

void FocusedAttributesWindow::setManaText(int value, float max_value){

	sf::Color mana_color = sf::Color::Green;
	if (value >= 0 && (value/max_value) <= 0.2f){

		mana_color = sf::Color::Red;

	}
	else if (value / max_value <= 0.4f){

		mana_color = sf::Color::Yellow;

	}

	mana_text.setColor(mana_color);
	mana_text.setString("MP " + std::to_string(value));
}

void FocusedAttributesWindow::setChargeText(int value, float max_value){

	sf::Color charge_text_color = sf::Color::Green;
	if (value >= 0 && (value / max_value) <= 0.2f){

		charge_text_color = sf::Color::Red;

	}
	else if ( value / max_value <= 0.4f){

		charge_text_color = sf::Color::Yellow;

	}

	charge_text.setColor(charge_text_color);
	charge_text.setString("CP " + std::to_string(value));

}

void FocusedAttributesWindow::setLevelText(int level){

	level_txt.setString("Level " + std::to_string(level));

}

void FocusedAttributesWindow::setExperienceText(int value){

	exp_text.setString("XP " + std::to_string(value));
}

void FocusedAttributesWindow::setCoordinates(float x, float y){

	//The coordinates of the player
	const sf::String coordinates_status = "X: " + std::to_string( (int) x)  + " Y: " + std::to_string((int)y);
	coords_text.setString(coordinates_status);

}
