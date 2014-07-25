#ifndef MESSAGE_WINDOW_H
#define MESSAGE_WINDOW_H
#include "SFML\Graphics.hpp"

class MessageWindow{

public:
	MessageWindow();
	MessageWindow(int x_pos, int y_pos, int width, int height, int size);
	~MessageWindow();

	void update(float x, float y, long elapsed);
	void draw(sf::RenderWindow*);
	void setFont(sf::Font&);
	bool setMessage(std::string, long Timer, sf::Color color);
	void setMessageTimer(long);
	void setPosition(float x, float y);
	void setMsgPosition(float, float);

	sf::Font& getFont();
	long getMessageTimer();
	sf::Text& getMessage();
	sf::Color getMessageColor();

	void setMessageColor(sf::Color);
	bool hasMessage();
	bool hasMessageTimeExpired();

protected:
	sf::RectangleShape message_window_background;
	sf::RectangleShape message_window_pic;
	sf::Text message;

private:
	long messageTimer;
	sf::String msg;
	int message_index;
	sf::Font font;
	int float_text_amount;
	int float_color_amount;
};

#endif