#include "../headers/stdafx.h"
#include "../headers/MessageWindow.h"

MessageWindow::MessageWindow(){

	messageTimer = 1000;
	font.loadFromFile("arial.ttf");
	this->setFont(font);
	message.setCharacterSize(16);
	message.setString("");
	message_window_background.setSize(sf::Vector2f(100, 28));
	message_window_background.setFillColor(sf::Color(0, 0, 0, 20));
	message_window_background.setPosition(0, 0);//Temporary, this will be adjusted based on the window's size

	message_window_pic.setSize(sf::Vector2f(64, 64));
	message_window_pic.setFillColor(sf::Color(255, 255, 255, 0));
	message_window_pic.setPosition(message_window_background.getPosition().x + 10, message_window_background.getPosition().y);

	message.setPosition(message_window_background.getPosition().x, 64);

	float_text_amount = 0;
	float_color_amount = 255;
}
MessageWindow::MessageWindow(int x_pos, int y_pos, int width, int height, int size){

	

	font.loadFromFile("arial.ttf");
	this->setFont(font);
	message.setCharacterSize(size);
	message.setString("");
	message_window_background.setSize(sf::Vector2f(width, height));
	message_window_background.setFillColor(sf::Color(0, 0, 0, 20));
	message_window_background.setPosition(x_pos, y_pos);//Temporary, this will be adjusted based on the window's size

	message_window_pic.setSize(sf::Vector2f(64, 64));
	message_window_pic.setFillColor(sf::Color(255, 255, 255, 0));
	message_window_pic.setPosition(message_window_background.getPosition().x + 10, message_window_background.getPosition().y);
	
	message.setPosition(message_window_background.getPosition().x, 64 );

	float_text_amount = 0;
	float_color_amount = 255;
}


void MessageWindow::setMessageColor(sf::Color color){

	message.setColor(color);
}

void MessageWindow::setFont(sf::Font& font){

	message.setFont(font);
}

void MessageWindow::draw(sf::RenderWindow* window){

	window->draw(message_window_background);
	window->draw(message_window_pic);
	window->draw(message);
}


bool MessageWindow::hasMessageTimeExpired(){

	return messageTimer <= 0;
}



sf::Font& MessageWindow::getFont(){

	return font;
}
sf::Color MessageWindow::getMessageColor(){


	return message.getColor();
}


long MessageWindow::getMessageTimer(){

	return messageTimer;
}

void MessageWindow::setMessageTimer(long value){

	messageTimer = value;
}

bool MessageWindow::hasMessage(){
	return message.getString() != "";
}


sf::Text& MessageWindow::getMessage(){

	return message;
}

void MessageWindow::setPosition(float x, float y){

	message_window_background.setPosition(x, y);

}

void MessageWindow::setMsgPosition(float x, float y){


	message.setPosition(x, y );
}

void MessageWindow::update(float x, float y, long elapsed){

	setMsgPosition(x, y - float_text_amount);
	setPosition(x, y - float_text_amount);
	setMessageColor(sf::Color(
	getMessageColor().r,
	getMessageColor().g,
	getMessageColor().b,
		float_color_amount));

	float_text_amount += 4;
	float_color_amount -= 2;
	if (float_text_amount >= 64){//Max float up value
		float_text_amount = 0;
		float_color_amount = 255;
	}

}

bool MessageWindow::setMessage(std::string text, long Timer, sf::Color color){

	message.setString( text );
	setMessageColor(color);
	this->messageTimer = Timer;
	return true;
}

MessageWindow::~MessageWindow()
{
}
