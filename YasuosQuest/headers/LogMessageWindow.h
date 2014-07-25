#pragma once
#include "MessageWindow.h"
#include <list>

class LogMessageWindow : public MessageWindow{
public:
	LogMessageWindow(int x, int y, int width, int height, int size);
		;
	~LogMessageWindow();

	void addMessage(sf::Text);
	void draw(sf::RenderWindow* window);
	sf::Vector2f getSize();
private:

	std::list<sf::Text> msg_queue;

};

